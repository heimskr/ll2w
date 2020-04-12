#ifndef PARSER_NODES_H_
#define PARSER_NODES_H_

#include <memory>
#include <tuple>
#include <unordered_set>

#include "parser/ASTNode.h"
#include "parser/Enums.h"
#include "parser/Types.h"
#include "parser/Values.h"
#include "parser/Lexer.h"
#include "parser/Constant.h"

namespace LL2W {
	class Variable;

	enum class NodeType {
		Metadata, Header, Attributes, Select, Alloca, Store, Load, Icmp, BrUncond, BrCond, CallInvoke,
		Call, Invoke, Getelementptr, Ret, Landingpad, Conversion, BasicMath, Phi, Simple, Div, Rem, Logic, Shr, FMath,
		Switch, ExtractValue, InsertValue, Resume, Unreachable, Asm
	};

	struct BaseNode: public ASTNode {
		using ASTNode::ASTNode;
		virtual NodeType nodeType() const = 0;
	};

	struct MetadataDef: public BaseNode {
		bool distinct;
		MetadataDef(ASTNode *decvar, ASTNode *distinct, ASTNode *list);
		std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Metadata; }
	};

	struct HeaderNode: public BaseNode {
		int label;
		std::vector<int> preds;
		HeaderNode(ASTNode *node);
		virtual std::string style() const override { return "\e[32m"; }
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Header; }
	};

	struct AttributesNode: public BaseNode {
		int index;
		int allocsizeSize = -1;
		int allocsizeCount = -1;
		std::unordered_set<FnAttr> basicAttributes;
		std::unordered_map<const std::string *, const std::string *> stringAttributes;
		AttributesNode(ASTNode *);
		virtual std::string style() const override { return "\e[31m"; }
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Attributes; }
	};

	class InstructionNode: public BaseNode {
		protected:
			void handleUnibangs(ASTNode *);

		public:
			int prof = -1;
			InstructionNode(const std::string *str);
			InstructionNode();
			virtual std::string style() const override { return "\e[36m"; }
	};

	struct Reader {
		virtual std::vector<ValuePtr> allValues() const = 0;
		virtual std::vector<ValuePtr *> allValuePointers() = 0;
		std::vector<std::shared_ptr<LocalValue>> allLocals() const;
		void replaceRead(std::shared_ptr<Variable> to_replace, std::shared_ptr<Variable> new_var);
	};

	struct Writer {
		const std::string *result = nullptr;
		std::shared_ptr<Variable> variable = nullptr;
		std::string getResult() const;
	};

	struct SelectNode: public InstructionNode, public Reader, public Writer {
		std::unordered_set<Fastmath> fastmath;
		TypePtr conditionType, firstType, secondType;
		ValuePtr conditionValue, firstValue, secondValue;

		SelectNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *condition_type, ASTNode *condition_value,
		           ASTNode *type1, ASTNode *val1, ASTNode *type2, ASTNode *val2, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Select; }
		virtual std::vector<ValuePtr> allValues() const override { return {conditionValue, firstValue, secondValue}; }
		virtual std::vector<ValuePtr *> allValuePointers() override {
			return {&conditionValue, &firstValue, &secondValue};
		}
	};

	struct AllocaNode: public InstructionNode, public Reader, public Writer {
		bool inalloca = false;
		TypePtr type;
		TypePtr numelementsType = nullptr;
		ValuePtr numelementsValue = nullptr;
		int align = -1;
		int addrspace = -1;

		AllocaNode(ASTNode *result_, ASTNode *inalloca_, ASTNode *type_, ASTNode *numelements_, ASTNode *align_,
		           ASTNode *addrspace_, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Alloca; }
		virtual std::vector<ValuePtr> allValues() const override { return {numelementsValue}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&numelementsValue}; }
	};

	class StoreNode: public InstructionNode, public Reader {
		private:
			void handleBangs(ASTNode *);

		public:
			bool volatile_ = false, atomic = false;
			TypePtr type;
			ValuePtr value;
			ConstantPtr constant;
			int align = -1, nontemporalIndex = -1, invariantGroupIndex = -1, tbaa = -1;
			const std::string *syncscope = nullptr;
			Ordering ordering = Ordering::None;

			StoreNode(ASTNode *volatile__, ASTNode *type_, ASTNode *value_, ASTNode *constant_, ASTNode *align_,
					ASTNode *bangs);
			StoreNode(ASTNode *volatile__, ASTNode *type_, ASTNode *value_, ASTNode *constant_, ASTNode *syncscope_,
					ASTNode *ordering_, ASTNode *align_, ASTNode *bangs);
			virtual std::string debugExtra() const override;
			virtual NodeType nodeType() const override { return NodeType::Store; }
			virtual std::vector<ValuePtr> allValues() const override { return {value, constant->value}; }
			virtual std::vector<ValuePtr *> allValuePointers() override { return {&value, &constant->value}; }
	};

	class LoadNode: public InstructionNode, public Writer, public Reader {
		private:
			void handleBangs(ASTNode *);

		public:
			bool volatile_ = false, atomic = false;
			TypePtr type;
			ConstantPtr constant;
			int align = -1, nontemporalIndex = -1, invariantLoadIndex = -1, invariantGroupIndex = -1,
				nonnullIndex = -1, tbaa = -1;
			const std::string *dereferenceable = nullptr, *dereferenceableOrNull = nullptr, *bangAlign = nullptr;
			const std::string *syncscope = nullptr;
			Ordering ordering = Ordering::None;

			LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_, ASTNode *align_,
					ASTNode *bangs);
			LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_,
					ASTNode *syncscope_, ASTNode *ordering_, ASTNode *align_, ASTNode *invariant_group);
			virtual std::string debugExtra() const override;
			virtual NodeType nodeType() const override { return NodeType::Load; }
			virtual std::vector<ValuePtr> allValues() const override { return {constant->value}; }
			virtual std::vector<ValuePtr *> allValuePointers() override { return {&constant->value}; }
	};

	struct IcmpNode: public InstructionNode, public Writer, public Reader {
		IcmpCond cond;
		TypePtr type;
		ValuePtr value1, value2;

		IcmpNode(ASTNode *result_, ASTNode *cond_, ASTNode *type_, ASTNode *op1, ASTNode *op2, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Icmp; }
		virtual std::vector<ValuePtr> allValues() const override { return {value1, value2}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&value1, &value2}; }
	};

	struct BrUncondNode: public InstructionNode {
		const std::string *destination;
		BrUncondNode(const std::string *destination_): destination(destination_) {}
		BrUncondNode(const std::string &destination_): BrUncondNode(StringSet::intern(destination_)) {}
		BrUncondNode(ASTNode *node, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::BrUncond; }
	};

	struct BrCondNode: public InstructionNode, public Reader {
		ValuePtr condition;
		const std::string *ifTrue, *ifFalse;

		BrCondNode(ASTNode *type, ASTNode *condition_, ASTNode *if_true, ASTNode *if_false, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::BrCond; }
		virtual std::vector<ValuePtr> allValues() const override { return {condition}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&condition}; }
	};

	class CallInvokeNode: public InstructionNode, public Writer, public Reader {
		protected:
			CallInvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
			               ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
			               ASTNode *attribute_list, ASTNode *unibangs);

		public:
			const std::string *cconv = nullptr;
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

			virtual std::vector<ValuePtr> allValues() const override;
			virtual std::vector<ValuePtr *> allValuePointers() override;
	};

	struct CallNode: public CallInvokeNode {
		const std::string *tail = nullptr;
		std::unordered_set<Fastmath> fastmath;

		CallNode(ASTNode *_result, ASTNode *_tail, ASTNode *fastmath_flags, ASTNode *_cconv, ASTNode *_retattrs,
		         ASTNode *_addrspace, ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
		         ASTNode *attribute_list, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Call; }
	};

	struct AsmNode: public CallInvokeNode {
		const std::string *contents = nullptr;
		const std::string *constraints = nullptr;
		bool sideeffect = false;
		bool alignstack = false;
		int srcloc = -1;

		AsmNode(ASTNode *_result, ASTNode *_retattrs, ASTNode *return_type, ASTNode *_args, ASTNode *_sideeffect,
		        ASTNode *_alignstack, ASTNode *_inteldialect, ASTNode *asm_string, ASTNode *asm_constraints,
		        ASTNode *_constants, ASTNode *attribute_list, ASTNode *_srcloc, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Asm; }
	};

	struct InvokeNode: public CallInvokeNode {
		const std::string *normalLabel, *exceptionLabel;

		InvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace, ASTNode *return_type,
		           ASTNode *_args, ASTNode *function_name, ASTNode *_constants, ASTNode *attribute_list,
		           ASTNode *normal_label, ASTNode *exception_label, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Invoke; }
	};

	struct GetelementptrNode: public InstructionNode, public Writer, public Reader {
		bool inbounds = false;
		TypePtr type = nullptr, ptrType = nullptr;
		ValuePtr ptrValue;
		// width, value/index, has minrange, is pvar
		std::vector<std::tuple<int, int, bool, bool>> indices;

		GetelementptrNode(ASTNode *pvar, ASTNode *_inbounds, ASTNode *type_, ASTNode *ptr_type, ASTNode *ptr_value,
		                  ASTNode *indices_, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Getelementptr; }
		virtual std::vector<ValuePtr> allValues() const override { return {ptrValue}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&ptrValue}; }
	};

	struct RetNode: public InstructionNode, public Reader {
		TypePtr type;
		ValuePtr value;

		RetNode(ASTNode *unibangs);
		RetNode(ASTNode *type_, ASTNode *value_, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Ret; }
		virtual std::vector<ValuePtr> allValues() const override { return {value}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&value}; }
	};

	struct LandingpadNode: public InstructionNode, public Writer, public Reader {
		struct Clause {
			enum class ClauseType {Catch, Filter};
			ClauseType clauseType;
			TypePtr type = nullptr;
			ValuePtr value = nullptr;
			Clause(ASTNode *);
			operator std::string() const;
		};

		TypePtr type;
		bool cleanup;
		std::vector<std::shared_ptr<Clause>> clauses;

		LandingpadNode(ASTNode *result_, ASTNode *type_, ASTNode *clauses_, ASTNode *unibangs, bool cleanup_);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Landingpad; }
		virtual std::vector<ValuePtr> allValues() const override;
		virtual std::vector<ValuePtr *> allValuePointers() override;
	};

	struct ConversionNode: public InstructionNode, public Writer, public Reader {
		TypePtr from, to;
		ValuePtr value;
		Conversion conversionType;
		ConversionNode(ASTNode *result_, ASTNode *conv_op, ASTNode *from_, ASTNode *value_, ASTNode *to_,
		               ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Conversion; }
		virtual std::vector<ValuePtr> allValues() const override { return {value}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&value}; }
	};

	struct BasicMathNode: public InstructionNode, public Writer, public Reader {
		const std::string *oper;
		int operSymbol;
		bool nuw = false, nsw = false;
		TypePtr type;
		ValuePtr left, right;
		BasicMathNode(ASTNode *result_, ASTNode *oper_, bool nuw_, bool nsw_, ASTNode *type_, ASTNode *left_,
		              ASTNode *right_, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::BasicMath; }
		virtual std::vector<ValuePtr> allValues() const override { return {left, right}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&left, &right}; }
	};

	struct PhiNode: public InstructionNode, public Writer {
		/** Whether all operands are local variables. */
		bool pure = true;
		std::unordered_set<Fastmath> fastmath;
		TypePtr type;
		std::vector<std::pair<ValuePtr, const std::string *>> pairs;
		PhiNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *type_, ASTNode *pairs_, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Phi; }
	};

	struct SimpleNode: public InstructionNode, public Writer, public Reader {
		TypePtr type;
		ValuePtr left, right;
		SimpleNode(ASTNode *result_, ASTNode *type_, ASTNode *left_, ASTNode *right_, ASTNode *unibangs);
		virtual const char * typeName() const = 0;
		virtual std::string debugExtra() const override;
		virtual std::vector<ValuePtr> allValues() const override { return {left, right}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&left, &right}; }
	};

	struct DivNode: public SimpleNode {
		enum class DivType {Sdiv, Udiv};
		DivType divType;
		DivNode(ASTNode *result_, ASTNode *div, ASTNode *type_, ASTNode *left_, ASTNode *right_, ASTNode *unibangs);
		virtual const char * typeName() const override { return divType == DivType::Sdiv? "sdiv" : "udiv"; }
		virtual NodeType nodeType() const override { return NodeType::Div; }
	};

	struct RemNode: public SimpleNode {
		enum class RemType {Srem, Urem};
		RemType remType;
		RemNode(ASTNode *result_, ASTNode *rem, ASTNode *type_, ASTNode *left_, ASTNode *right_, ASTNode *unibangs);
		virtual const char * typeName() const override { return remType == RemType::Srem? "srem" : "urem"; }
		virtual NodeType nodeType() const override { return NodeType::Rem; }
	};

	struct LogicNode: public SimpleNode {
		enum class LogicType {And, Or, Xor};
		LogicType logicType;
		LogicNode(ASTNode *result_, ASTNode *logic, ASTNode *type_, ASTNode *left_, ASTNode *right_, ASTNode *unibangs);
		const char * typeName() const override;
		virtual NodeType nodeType() const override { return NodeType::Logic; }
	};

	struct ShrNode: public SimpleNode {
		enum class ShrType {Lshr, Ashr};
		ShrType shrType;
		bool exact = false;
		ShrNode(ASTNode *result_, ASTNode *shr, ASTNode *exact_, ASTNode *type_, ASTNode *left_, ASTNode *right_,
		        ASTNode *unibangs);
		const char * typeName() const override { return shrType == ShrType::Lshr? "lshr" : "ashr"; }
		virtual NodeType nodeType() const override { return NodeType::Shr; }
	};

	struct FMathNode: public SimpleNode {
		enum class FMathType {Fadd, Fsub, Fmul, Fdiv, Frem};
		FMathType fmathType;
		std::unordered_set<Fastmath> fastmath;
		FMathNode(ASTNode *result_, ASTNode *fmath, ASTNode *flags, ASTNode *type_, ASTNode *left_, ASTNode *right_,
		          ASTNode *unibangs);
		const char * typeName() const override;
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::FMath; }
	};

	struct SwitchNode: public InstructionNode, public Reader {
		TypePtr type;
		ValuePtr value;
		const std::string *label;
		std::vector<std::tuple<TypePtr, ValuePtr, const std::string *>> table;

		SwitchNode(ASTNode *type_, ASTNode *value_, ASTNode *label_, ASTNode *table_, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Switch; }
		virtual std::vector<ValuePtr> allValues() const override { return {value}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&value}; }
	};

	struct ExtractValueNode: public InstructionNode, public Writer, public Reader {
		std::shared_ptr<AggregateType> aggregateType;
		ValuePtr aggregateValue;
		std::vector<int> decimals;
		ExtractValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value, ASTNode *decimals_,
		                 ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::ExtractValue; }
		virtual std::vector<ValuePtr> allValues() const override { return {aggregateValue}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&aggregateValue}; }
	};

	struct InsertValueNode: public InstructionNode, public Writer, public Reader {
		TypePtr aggregateType, type;
		ValuePtr aggregateValue, value;
		std::vector<int> decimals;
		InsertValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value, ASTNode *type_,
		                ASTNode *value_, ASTNode *decimals_, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::InsertValue; }
		virtual std::vector<ValuePtr> allValues() const override { return {aggregateValue, value}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&aggregateValue, &value}; }
	};

	struct ResumeNode: public InstructionNode, public Reader {
		TypePtr type;
		ValuePtr value;
		ResumeNode(ASTNode *type_, ASTNode *value_, ASTNode *unibangs);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Resume; }
		virtual std::vector<ValuePtr> allValues() const override { return {value}; }
		virtual std::vector<ValuePtr *> allValuePointers() override { return {&value}; }
	};

	struct UnreachableNode: public InstructionNode {
		UnreachableNode() {}
		virtual std::string debugExtra() const override { return "\e[91munreachable\e[39m"; }
		virtual NodeType nodeType() const override { return NodeType::Unreachable; }
	};
}

#endif
