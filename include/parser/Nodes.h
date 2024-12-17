#pragma once

#include "compiler/Variable.h"
#include "parser/ASTNode.h"
#include "parser/Enums.h"
#include "parser/Types.h"
#include "parser/Values.h"
#include "parser/Lexer.h"
#include "parser/Constant.h"
#include "util/Makeable.h"

#include <memory>
#include <tuple>
#include <unordered_set>
#include <variant>

namespace llvm {
	class AllocaInst;
	class CallInst;
	class Instruction;
	class LoadInst;
	class ReturnInst;
	class StoreInst;
}

namespace LL2W {
	class Variable;

	struct BaseNode: ASTNode {
		using ASTNode::ASTNode;
		virtual NodeType nodeType() const = 0;
	};

	struct HasType {
		TypePtr type;
	};

	struct HasValue {
		ValuePtr value;
	};

	struct HasConstant {
		ConstantPtr constant;
	};

	struct MetadataDef: BaseNode {
		bool distinct = false;
		MetadataDef(ASTNode *decvar, ASTNode *distinct, ASTNode *list);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Metadata; }
	};

	struct HeaderNode: BaseNode {
		const std::string *label;
		std::vector<const std::string *> preds;
		HeaderNode(bool simple, ASTNode *);
		HeaderNode(ASTNode *);
		std::string style() const override { return "\e[32m"; }
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Header; }
	};

	struct AttributesNode: BaseNode {
		int index;
		int allocsizeSize = -1;
		int allocsizeCount = -1;
		std::unordered_set<ParAttr> parameterAttributes;
		std::unordered_set<FnAttr> functionAttributes;
		std::unordered_map<const std::string *, const std::string *> stringAttributes;
		AttributesNode(ASTNode *);
		std::string style() const override { return "\e[31m"; }
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Attributes; }
	};

	class InstructionNode: public BaseNode {
		protected:
			void handleUnibangs(ASTNode *);

		public:
			int prof = -1, callees = -1;
			InstructionNode(const std::string *str);
			InstructionNode();
			std::string style() const override { return "\e[36m"; }
			virtual InstructionNode * copy() const = 0;

			static InstructionNode * fromLLVM(llvm::Instruction *);
	};

	struct Reader {
		virtual std::vector<ValuePtr> allValues() = 0;
		virtual std::vector<ValuePtr *> allValuePointers() = 0;
		std::vector<std::shared_ptr<LocalValue>> allLocals();
		void replaceRead(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var);
		virtual std::vector<ConstantPtr> allConstants() const { return {}; }
		virtual std::vector<ConstantPtr *> allConstantPointers() { return {}; }
	};

	struct Writer {
		const std::string *result = nullptr;
		std::shared_ptr<Variable> variable = nullptr;
		void replaceWritten(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var);
		std::string getResult() const;
	};

	struct CachedConstantValue {
		ValuePtr cachedConstantValue;
	};

	struct SelectNode: InstructionNode, Reader, Writer {
		std::unordered_set<Fastmath> fastmath;
		TypePtr conditionType, firstType, secondType;
		ValuePtr conditionValue, firstValue, secondValue;

		SelectNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *condition_type, ASTNode *condition_value,
		           ASTNode *type1, ASTNode *val1, ASTNode *type2, ASTNode *val2, ASTNode *unibangs);
		SelectNode(const std::string *result_, std::unordered_set<Fastmath>, TypePtr condition_type, TypePtr first_type,
		           TypePtr second_type, ValuePtr condition_value, ValuePtr first_value, ValuePtr second_value,
		           int debug_index);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Select; }
		std::vector<ValuePtr> allValues() override { return {conditionValue, firstValue, secondValue}; }
		std::vector<ValuePtr *> allValuePointers() override {
			return {&conditionValue, &firstValue, &secondValue};
		}
		InstructionNode * copy() const override;
	};

	struct AllocaNode: InstructionNode, Reader, Writer, HasType {
		bool inalloca = false;
		TypePtr numelementsType;
		ValuePtr numelementsValue;
		int align = -1;
		int addrspace = -1;

		AllocaNode(const llvm::AllocaInst &);
		AllocaNode(ASTNode *result_, ASTNode *inalloca_, ASTNode *type_, ASTNode *numelements_, ASTNode *align_,
		           ASTNode *addrspace_, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Alloca; }
		std::vector<ValuePtr> allValues() override { return {numelementsValue}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&numelementsValue}; }
		InstructionNode * copy() const override;
	};

	class StoreNode: public InstructionNode, public Reader {
		private:
			void handleBangs(ASTNode *);

		public:
			bool volatile_ = false;
			bool atomic = false;
			ConstantPtr source;
			ConstantPtr destination;
			int align = -1;
			int nontemporalIndex = -1;
			int invariantGroupIndex = -1;
			int tbaa = -1;
			const std::string *syncscope = nullptr;
			Ordering ordering = Ordering::None;

			StoreNode(const llvm::StoreInst &);
			StoreNode(ASTNode *volatile__, ASTNode *source_, ASTNode *destination_, ASTNode *align_, ASTNode *bangs);
			StoreNode(ASTNode *volatile__, ASTNode *source_, ASTNode *destination_, ASTNode *syncscope_, ASTNode *ordering_, ASTNode *align_, ASTNode *bangs);
			std::string debugExtra() const override;
			NodeType nodeType() const override { return NodeType::Store; }
			std::vector<ValuePtr> allValues() override;
			std::vector<ValuePtr *> allValuePointers() override;
			std::vector<ConstantPtr> allConstants() const override { return {source, destination}; }
			std::vector<ConstantPtr *> allConstantPointers() override { return {&source, &destination}; }
			InstructionNode * copy() const override;
	};

	class LoadNode: public InstructionNode, public Writer, public Reader {
		private:
			void handleBangs(ASTNode *);

		public:
			bool volatile_ = false, atomic = false;
			TypePtr type;
			ConstantPtr constant;
			int align = -1;
			int nontemporalIndex = -1;
			int invariantLoadIndex = -1;
			int invariantGroupIndex = -1;
			int nonnullIndex = -1;
			int tbaa = -1;
			const std::string *dereferenceable = nullptr;
			const std::string *dereferenceableOrNull = nullptr;
			const std::string *bangAlign = nullptr;
			const std::string *syncscope = nullptr;
			Ordering ordering = Ordering::None;

			LoadNode(const llvm::LoadInst &);
			LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_, ASTNode *align_, ASTNode *bangs);
			LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_, ASTNode *syncscope_, ASTNode *ordering_, ASTNode *align_, ASTNode *invariant_group);
			std::string debugExtra() const override;
			NodeType nodeType() const override { return NodeType::Load; }
			std::vector<ValuePtr> allValues() override { return {constant->value}; }
			std::vector<ValuePtr *> allValuePointers() override { return {&constant->value}; }
			std::vector<ConstantPtr> allConstants() const override { return {constant}; }
			std::vector<ConstantPtr *> allConstantPointers() override { return {&constant}; }
			InstructionNode * copy() const override;
	};

	struct IcmpNode: InstructionNode, Writer, Reader, Makeable<IcmpNode> {
		IcmpCond cond;
		ConstantPtr left, right;

		IcmpNode(ASTNode *result_, ASTNode *cond_, ASTNode *left_, ASTNode *right_, ASTNode *unibangs);
		IcmpNode(const std::string *result_, IcmpCond cond_, ConstantPtr left_, ConstantPtr right_);
		IcmpNode(VariablePtr variable_, IcmpCond cond_, ConstantPtr left_, ConstantPtr right_);
		TypePtr getType() const { return left->type; }
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Icmp; }
		std::vector<ValuePtr> allValues() override;
		std::vector<ValuePtr *> allValuePointers() override;
		std::vector<ConstantPtr> allConstants() const override;
		std::vector<ConstantPtr *> allConstantPointers() override;
		InstructionNode * copy() const override;
	};

	struct BrUncondNode: InstructionNode {
		const std::string *destination;
		BrUncondNode(const std::string *destination_): destination(destination_) {}
		BrUncondNode(const std::string &destination_): BrUncondNode(StringSet::intern(destination_)) {}
		BrUncondNode(ASTNode *node, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::BrUncond; }
		InstructionNode * copy() const override;
	};

	struct BrCondNode: InstructionNode, Reader {
		ConstantPtr condition;
		const std::string *ifTrue, *ifFalse;

		BrCondNode(ASTNode *constant, ASTNode *if_true, ASTNode *if_false, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::BrCond; }
		std::vector<ValuePtr> allValues() override { return {condition->value}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&condition->value}; }
		std::vector<ConstantPtr> allConstants() const override { return {condition}; }
		std::vector<ConstantPtr *> allConstantPointers() override { return {&condition}; }
		InstructionNode * copy() const override;
	};

	class CallInvokeNode: public InstructionNode, public Writer, public Reader {
		protected:
			CallInvokeNode(const llvm::CallInst &);
			CallInvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
			               ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
			               ASTNode *attribute_list, ASTNode *unibangs);

		public:
			CConv cconv = CConv::ccc;
			std::unordered_set<RetAttr> retattrs;
			std::vector<ConstantPtr> constants;
			std::vector<int> attributeIndices;
			int dereferenceable = -1, addrspace = -1;

			// For functions with varargs (and optionally for non-varargs functions), the function argument types can be
			// specified after the function return type.
			bool argumentsExplicit = false;
			std::vector<TypePtr> argumentTypes;
			bool argumentEllipsis = false;

			TypePtr returnType;
			ValuePtr name;

			std::vector<ValuePtr> allValues() override;
			std::vector<ValuePtr *> allValuePointers() override;
			std::vector<ConstantPtr> allConstants() const override { return constants; }
			std::vector<ConstantPtr *> allConstantPointers() override;

		protected:
			CallInvokeNode * copyTo(CallInvokeNode &) const;
	};

	struct CallNode: CallInvokeNode {
		TailCallKind tail = TailCallKind::None;
		std::unordered_set<Fastmath> fastmath;

		CallNode(const llvm::CallInst &);
		CallNode(ASTNode *_result, ASTNode *_tail, ASTNode *fastmath_flags, ASTNode *_cconv, ASTNode *_retattrs,
		         ASTNode *_addrspace, ASTNode *return_type, ASTNode *_args, ASTNode *constant, ASTNode *_constants,
		         ASTNode *attribute_list, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Call; }
		InstructionNode * copy() const override;
	};

	struct AsmNode: CallInvokeNode {
		const std::string *contents = nullptr;
		const std::string *constraints = nullptr;
		bool sideeffect = false;
		bool alignstack = false;
		int srcloc = -1;

		AsmNode(ASTNode *_result, ASTNode *_retattrs, ASTNode *return_type, ASTNode *_args, ASTNode *_sideeffect,
		        ASTNode *_alignstack, ASTNode *_inteldialect, ASTNode *asm_string, ASTNode *asm_constraints,
		        ASTNode *_constants, ASTNode *attribute_list, ASTNode *_srcloc, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Asm; }
		InstructionNode * copy() const override;
	};

	struct InvokeNode: CallInvokeNode {
		const std::string *normalLabel, *exceptionLabel;

		InvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace, ASTNode *return_type,
		           ASTNode *_args, ASTNode *constant, ASTNode *_constants, ASTNode *attribute_list,
		           ASTNode *normal_label, ASTNode *exception_label, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Invoke; }
		InstructionNode * copy() const override;
	};

	struct GetelementptrNode: InstructionNode, Writer, Reader, CachedConstantValue {
		struct Index {
			long width;
			std::variant<long, Variable::ID> value;
			bool hasMinrange;
			bool isPvar;
			Index(long width_, const decltype(value) &value_, bool has_minrange, bool is_pvar):
				width(width_), value(value_), hasMinrange(has_minrange), isPvar(is_pvar) {}
		};

		bool inbounds = false;
		TypePtr type, pointerType;
		ConstantPtr constant;
		std::vector<Index> indices;

		GetelementptrNode(ASTNode *pvar, ASTNode *_inbounds, ASTNode *type_, ASTNode *constant_, ASTNode *indices_,
		                  ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Getelementptr; }
		std::vector<ValuePtr> allValues() override;
		std::vector<ValuePtr *> allValuePointers() override;
		InstructionNode * copy() const override;
	};

	struct RetNode: InstructionNode, Reader {
		TypePtr type;
		ValuePtr value;

		RetNode(const llvm::ReturnInst &);
		RetNode(ASTNode *unibangs);
		RetNode(ASTNode *type_, ASTNode *value_, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Ret; }
		std::vector<ValuePtr> allValues() override { return {value}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&value}; }
		InstructionNode * copy() const override;
	};

	struct LandingpadNode: InstructionNode, Writer, Reader {
		struct Clause {
			enum class ClauseType {Catch, Filter};
			ClauseType clauseType;
			TypePtr type = nullptr;
			ValuePtr value = nullptr;
			Clause(ASTNode *);
			operator std::string() const;
			Clause * copy() const;
		};

		TypePtr type;
		bool cleanup;
		std::vector<std::shared_ptr<Clause>> clauses;

		LandingpadNode(ASTNode *result_, ASTNode *type_, ASTNode *clauses_, ASTNode *unibangs, bool cleanup_);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Landingpad; }
		std::vector<ValuePtr> allValues() override;
		std::vector<ValuePtr *> allValuePointers() override;
		InstructionNode * copy() const override;
	};

	struct ConversionNode: InstructionNode, Writer, Reader {
		TypePtr from;
		TypePtr to;
		ValuePtr value;
		Conversion conversionType;
		ConversionNode(ASTNode *result_, ASTNode *conv_op, ASTNode *from_, ASTNode *value_, ASTNode *to_,
		               ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Conversion; }
		std::vector<ValuePtr> allValues() override { return {value}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&value}; }
		InstructionNode * copy() const override;
	};

	struct BasicMathNode: InstructionNode, Writer, Reader {
		const std::string *oper;
		int operSymbol;
		bool nuw = false, nsw = false;
		TypePtr type;
		ValuePtr left;
		ValuePtr right;
		BasicMathNode(ASTNode *result_, ASTNode *oper_, bool nuw_, bool nsw_, ASTNode *type_, ASTNode *left_,
		              ASTNode *right_, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::BasicMath; }
		std::vector<ValuePtr> allValues() override { return {left, right}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&left, &right}; }
		InstructionNode * copy() const override;
	};

	struct PhiNode: InstructionNode, Reader, Writer {
		/** Whether all operands are local variables. */
		bool pure = true;
		std::unordered_set<Fastmath> fastmath;
		TypePtr type;
		std::vector<std::pair<ValuePtr, const std::string *>> pairs;
		PhiNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *type_, ASTNode *pairs_, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Phi; }
		std::vector<ValuePtr> allValues() override;
		std::vector<ValuePtr *> allValuePointers() override;
		InstructionNode * copy() const override;
	};

	struct SimpleNode: InstructionNode, Writer, Reader {
		TypePtr type;
		ValuePtr left;
		ValuePtr right;
		SimpleNode(ASTNode *result_, ASTNode *type_, ASTNode *left_, ASTNode *right_, ASTNode *unibangs);
		virtual const char * typeName() const = 0;
		std::string debugExtra() const override;
		std::vector<ValuePtr> allValues() override { return {left, right}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&left, &right}; }
	};

	struct DivNode: SimpleNode {
		enum class DivType {Sdiv, Udiv};
		DivType divType;
		bool exact = false;
		DivNode(ASTNode *result_, ASTNode *div, ASTNode *exact_, ASTNode *type_, ASTNode *left_, ASTNode *right_,
		        ASTNode *unibangs);
		const char * typeName() const override { return divType == DivType::Sdiv? "sdiv" : "udiv"; }
		NodeType nodeType() const override { return NodeType::Div; }
		InstructionNode * copy() const override;
	};

	struct RemNode: SimpleNode {
		enum class RemType {Srem, Urem};
		RemType remType;
		bool exact = false;
		RemNode(ASTNode *result_, ASTNode *rem, ASTNode *exact_, ASTNode *type_, ASTNode *left_, ASTNode *right_,
		        ASTNode *unibangs);
		const char * typeName() const override { return remType == RemType::Srem? "srem" : "urem"; }
		NodeType nodeType() const override { return NodeType::Rem; }
		InstructionNode * copy() const override;
	};

	struct LogicNode: InstructionNode, Writer, Reader, Makeable<LogicNode> {
		LogicType logicType;
		ConstantPtr left;
		ConstantPtr right;

		LogicNode(ASTNode *result_, ASTNode *logic_type, ASTNode *left_, ASTNode *right_, ASTNode *unibangs);
		LogicNode(const std::string *result_, LogicType logic_type, ConstantPtr left_, ConstantPtr right_);
		LogicNode(VariablePtr variable_, LogicType logic_type, ConstantPtr left_, ConstantPtr right_);
		TypePtr getType() const { return left->type; }
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Logic; }
		std::vector<ValuePtr> allValues() override;
		std::vector<ValuePtr *> allValuePointers() override;
		std::vector<ConstantPtr> allConstants() const override;
		std::vector<ConstantPtr *> allConstantPointers() override;
		InstructionNode * copy() const override;
	};

	struct ShrNode: SimpleNode {
		enum class ShrType {Lshr, Ashr};
		ShrType shrType;
		bool exact = false;
		ShrNode(ASTNode *result_, ASTNode *shr, ASTNode *exact_, ASTNode *type_, ASTNode *left_, ASTNode *right_,
		        ASTNode *unibangs);
		const char * typeName() const override { return shrType == ShrType::Lshr? "lshr" : "ashr"; }
		NodeType nodeType() const override { return NodeType::Shr; }
		InstructionNode * copy() const override;
	};

	struct FMathNode: SimpleNode {
		enum class FMathType {Fadd, Fsub, Fmul, Fdiv, Frem};
		FMathType fmathType;
		std::unordered_set<Fastmath> fastmath;
		FMathNode(ASTNode *result_, ASTNode *fmath, ASTNode *flags, ASTNode *type_, ASTNode *left_, ASTNode *right_,
		          ASTNode *unibangs);
		const char * typeName() const override;
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::FMath; }
		InstructionNode * copy() const override;
	};

	struct SwitchNode: InstructionNode, Reader {
		TypePtr type;
		ValuePtr value;
		const std::string *label;
		std::vector<std::tuple<TypePtr, ValuePtr, const std::string *>> table;
		SwitchNode(ASTNode *type_, ASTNode *value_, ASTNode *label_, ASTNode *table_, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Switch; }
		std::vector<ValuePtr> allValues() override { return {value}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&value}; }
		InstructionNode * copy() const override;
	};

	struct ExtractValueNode: InstructionNode, Writer, Reader {
		std::shared_ptr<AggregateType> aggregateType;
		ValuePtr aggregateValue;
		std::vector<int> decimals;
		ExtractValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value, ASTNode *decimals_,
		                 ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::ExtractValue; }
		std::vector<ValuePtr> allValues() override { return {aggregateValue}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&aggregateValue}; }
		InstructionNode * copy() const override;
	};

	struct InsertValueNode: InstructionNode, Writer, Reader {
		TypePtr aggregateType;
		TypePtr type;
		ValuePtr aggregateValue;
		ValuePtr value;
		std::vector<int> decimals;
		InsertValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value, ASTNode *type_,
		                ASTNode *value_, ASTNode *decimals_, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::InsertValue; }
		std::vector<ValuePtr> allValues() override { return {aggregateValue, value}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&aggregateValue, &value}; }
		InstructionNode * copy() const override;
	};

	struct ResumeNode: InstructionNode, Reader {
		TypePtr type;
		ValuePtr value;
		ResumeNode(ASTNode *type_, ASTNode *value_, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Resume; }
		std::vector<ValuePtr> allValues() override { return {value}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&value}; }
		InstructionNode * copy() const override;
	};

	struct UnreachableNode: InstructionNode {
		UnreachableNode() = default;
		std::string debugExtra() const override { return "\e[91munreachable\e[39m"; }
		NodeType nodeType() const override { return NodeType::Unreachable; }
		InstructionNode * copy() const override { return new UnreachableNode(*this); }
	};

	struct FreezeNode: InstructionNode, Writer, Reader {
		TypePtr type;
		ValuePtr value;
		FreezeNode(ASTNode *result_, ASTNode *type_, ASTNode *value_, ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Freeze; }
		std::vector<ValuePtr> allValues() override { return {value}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&value}; }
		InstructionNode * copy() const override;
	};

	struct DbgIntrinsicNode: InstructionNode {
		enum class Type {Invalid, Value, Declare};
		Type type = Type::Invalid;
		ConstantPtr constant;
		// TODO: make actual metadata class maybe?
		ASTNode *firstMetadata = nullptr;
		ASTNode *secondMetadata = nullptr;
		DbgIntrinsicNode(ASTNode *type_, ASTNode *constant_, ASTNode *first_metadata, ASTNode *second_metadata,
		                 ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::DbgDeclare; }
		InstructionNode * copy() const override;
	};

	struct AtomicrmwNode: InstructionNode, Writer, Reader {
		enum class Op {Invalid, Xchg, Add, Sub, And, Nand, Or, Xor, Max, Min, Umax, Umin, Fadd, Fsub, Fmax, Fmin};
		Op op = Op::Invalid;
		const std::string *opString = nullptr;
		bool volatile_ = false;
		TypePtr type;
		TypePtr pointerType;
		ValuePtr pointer;
		ValuePtr value;
		const std::string *syncscope = nullptr;
		Ordering ordering = Ordering::None;
		int64_t align = -1;

		AtomicrmwNode(ASTNode *result_, ASTNode *_volatile_, ASTNode *op_, ASTNode *pointer_type, ASTNode *pointer_,
		              ASTNode *type_, ASTNode *value_, ASTNode *syncscope_, ASTNode *ordering_, ASTNode *align_,
		              ASTNode *unibangs);
		std::string debugExtra() const override;
		NodeType nodeType() const override { return NodeType::Atomicrmw; }
		std::vector<ValuePtr> allValues() override { return {pointer, value}; }
		std::vector<ValuePtr *> allValuePointers() override { return {&pointer, &value}; }
		InstructionNode * copy() const override;

		static std::unordered_map<std::string, Op> opMap;
	};

	ASTNode * ignoreConversion(ASTNode *);
}
