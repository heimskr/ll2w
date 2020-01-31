#ifndef PARSER_NODES_H_
#define PARSER_NODES_H_

#include <unordered_set>
#include <tuple>

#include "ASTNode.h"
#include "Enums.h"
#include "Types.h"
#include "Values.h"
#include "Lexer.h"
#include "Constant.h"

namespace LL2W {
	enum class NodeType {
		Metadata, Header, Attributes, Select, Alloca, Store, Load, Icmp, BrUncond, BrCond, CallInvoke,
		Call, Invoke, Getelementptr, Ret, Landingpad, Conversion, BasicMath, Phi, Simple, Div, Rem, Logic, Shr, FMath,
		Switch, ExtractValue, InsertValue, Resume
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
		std::unordered_set<FnAttr> basicAttributes;
		std::unordered_map<const std::string *, const std::string *> stringAttributes;
		AttributesNode(ASTNode *);
		virtual std::string style() const override { return "\e[31m"; }
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Attributes; }
	};

	struct InstructionNode: public BaseNode {
		InstructionNode(const std::string *str): BaseNode(INSTRUCTION, str) {}
		InstructionNode(): BaseNode(INSTRUCTION, "") {}
		virtual std::string style() const override { return "\e[36m"; }
	};

	struct Reader {
		virtual std::vector<Value *> allValues() const = 0;
	};

	struct Writer {
		const std::string *result = nullptr;
	};

	struct SelectNode: public InstructionNode, public Reader, public Writer {
		std::unordered_set<Fastmath> fastmath;
		Type *conditionType, *firstType, *secondType;
		Value *conditionValue, *firstValue, *secondValue;

		SelectNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *condition_type, ASTNode *condition_value,
		           ASTNode *type1, ASTNode *val1, ASTNode *type2, ASTNode *val2);
		~SelectNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Select; }
		virtual std::vector<Value *> allValues() const override { return {conditionValue, firstValue, secondValue}; }
	};

	struct AllocaNode: public InstructionNode, public Reader, public Writer {
		bool inalloca = false;
		Type *type;
		Type *numelementsType = nullptr;
		Value *numelementsValue = nullptr;
		int align = -1;
		int addrspace = -1;

		AllocaNode(ASTNode *result_, ASTNode *inalloca_, ASTNode *type_, ASTNode *numelements_, ASTNode *align_,
		           ASTNode *addrspace_);
		~AllocaNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Alloca; }
		virtual std::vector<Value *> allValues() const override { return {numelementsValue}; }
	};

	struct StoreNode: public InstructionNode, public Reader {
		bool volatile_ = false, atomic = false;
		Type *type;
		Value *value;
		Constant *constant;
		int align = -1, nontemporalIndex = -1, invariantGroupIndex = -1;
		const std::string *syncscope = nullptr;
		Ordering ordering = Ordering::None;

		StoreNode(ASTNode *volatile__, ASTNode *type_, ASTNode *value_, ASTNode *constant_, ASTNode *align_,
		          ASTNode *nontemporal_, ASTNode *invariant_group);
		StoreNode(ASTNode *volatile__, ASTNode *type_, ASTNode *value_, ASTNode *constant_, ASTNode *syncscope_,
		          ASTNode *ordering_, ASTNode *align_, ASTNode *invariant_group);
		~StoreNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Store; }
		virtual std::vector<Value *> allValues() const override { return {value, constant->value}; }
	};

	struct LoadNode: public InstructionNode, public Writer, public Reader {
		bool volatile_ = false, atomic = false;
		Type *type;
		Constant *constant;
		int align = -1, nontemporalIndex = -1, invariantLoadIndex = -1, invariantGroupIndex = -1,
		    nonnullIndex = -1;
		const std::string *dereferenceable = nullptr, *dereferenceableOrNull = nullptr, *bangAlign = nullptr;
		const std::string *syncscope = nullptr;
		Ordering ordering = Ordering::None;

		LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_,
		         ASTNode *align_, ASTNode *nontemporal_, ASTNode *invariant_load, ASTNode *invariant_group,
		         ASTNode *nonnull_, ASTNode *dereferenceable_, ASTNode *dereferenceable_or_null, ASTNode *bang_align);
		LoadNode(ASTNode *result_, ASTNode *volatile__, ASTNode *type_, ASTNode *constant_,
		         ASTNode *syncscope_, ASTNode *ordering_, ASTNode *align_, ASTNode *invariant_group);
		~LoadNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Load; }
		virtual std::vector<Value *> allValues() const override { return {constant->value}; }
	};

	struct IcmpNode: public InstructionNode, public Writer, public Reader {
		const std::string *result;
		IcmpCond cond;
		Type *type;
		Value *value1, *value2;

		IcmpNode(ASTNode *result_, ASTNode *cond_, ASTNode *type_, ASTNode *op1, ASTNode *op2);
		~IcmpNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Icmp; }
		virtual std::vector<Value *> allValues() const override { return {value1, value2}; }
	};

	struct BrUncondNode: public InstructionNode {
		const std::string *destination;
		BrUncondNode(const std::string *destination_): destination(destination_) {}
		BrUncondNode(const std::string &destination_): BrUncondNode(&destination_) {}
		BrUncondNode(const ASTNode *node): BrUncondNode(node->lexerInfo) { delete node; }
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::BrUncond; }
	};

	struct BrCondNode: public InstructionNode, public Reader {
		Value *condition;
		const std::string *ifTrue, *ifFalse;

		BrCondNode(ASTNode *type, ASTNode *condition_, ASTNode *if_true, ASTNode *if_false);
		~BrCondNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::BrCond; }
		virtual std::vector<Value *> allValues() const override { return {condition}; }
	};

	class CallInvokeNode: public InstructionNode, public Writer, public Reader {
		protected:
			CallInvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
			               ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
			               ASTNode *attribute_list);

		public:
			const std::string *cconv = nullptr;
			std::unordered_set<RetAttr> retattrs;
			std::vector<Constant *> constants;
			std::vector<int> attributeIndices;
			int dereferenceable = -1, addrspace = -1;

			// For functions with varargs (and optionally for non-varargs functions), the function argument types can be
			// specified after the function return type.
			bool argumentsExplicit = false;
			std::vector<Type *> argumentTypes;
			bool argumentEllipsis = false;

			Type *returnType;
			VariableValue *name;

			~CallInvokeNode();
			virtual std::vector<Value *> allValues() const override;
	};

	struct CallNode: public CallInvokeNode {
		const std::string *tail = nullptr;
		std::unordered_set<Fastmath> fastmath;

		CallNode(ASTNode *_result, ASTNode *_tail, ASTNode *fastmath_flags, ASTNode *_cconv, ASTNode *_retattrs,
		         ASTNode *_addrspace, ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
		         ASTNode *attribute_list);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Call; }
	};

	struct InvokeNode: public CallInvokeNode {
		const std::string *normalLabel, *exceptionLabel;

		InvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace, ASTNode *return_type,
		           ASTNode *_args, ASTNode *function_name, ASTNode *_constants, ASTNode *attribute_list,
		           ASTNode *normal_label, ASTNode *exception_label);
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Invoke; }
	};

	struct GetelementptrNode: public InstructionNode, public Writer, public Reader {
		bool inbounds = false;
		Type *type = nullptr, *ptrType = nullptr;
		Value *ptrValue = nullptr;
		std::vector<std::tuple<int, int, bool>> indices;

		GetelementptrNode(ASTNode *pvar, ASTNode *_inbounds, ASTNode *type_, ASTNode *ptr_type, ASTNode *ptr_value,
		                  ASTNode *indices_);
		~GetelementptrNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Getelementptr; }
		virtual std::vector<Value *> allValues() const override { return {ptrValue}; }
	};

	struct RetNode: public InstructionNode, public Reader {
		Type *type;
		Value *value;

		RetNode();
		RetNode(ASTNode *type_, ASTNode *value_);
		~RetNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Ret; }
		virtual std::vector<Value *> allValues() const override { return {value}; }
	};

	struct LandingpadNode: public InstructionNode, public Writer, public Reader {
		struct Clause {
			enum class ClauseType {Catch, Filter};
			ClauseType clauseType;
			Type *type = nullptr;
			Value *value = nullptr;
			Clause(ASTNode *);
			~Clause();
			operator std::string() const;
		};

		Type *type;
		bool cleanup;
		std::vector<Clause *> clauses;

		LandingpadNode(ASTNode *result_, ASTNode *type_, ASTNode *clauses_, bool cleanup_);
		~LandingpadNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Landingpad; }
		virtual std::vector<Value *> allValues() const override;
	};

	struct ConversionNode: public InstructionNode, public Writer, public Reader {
		Type *from, *to;
		Value *value;
		Conversion conversionType;
		ConversionNode(ASTNode *result_, ASTNode *conv_op, ASTNode *from_, ASTNode *value_, ASTNode *to_);
		~ConversionNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Conversion; }
		virtual std::vector<Value *> allValues() const override { return {value}; }
	};

	struct BasicMathNode: public InstructionNode, public Writer, public Reader {
		const std::string *oper;
		int operSymbol;
		bool nuw = false, nsw = false;
		Type *type;
		Value *left, *right;
		BasicMathNode(ASTNode *result_, ASTNode *oper_, bool nuw_, bool nsw_, ASTNode *type_, ASTNode *left_,
		              ASTNode *right_);
		~BasicMathNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::BasicMath; }
		virtual std::vector<Value *> allValues() const override { return {left, right}; }
	};

	struct PhiNode: public InstructionNode, public Writer {
		std::unordered_set<Fastmath> fastmath;
		Type *type;
		std::vector<std::pair<Value *, const std::string *>> pairs;
		PhiNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *type_, ASTNode *pairs_);
		~PhiNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Phi; }
	};

	struct SimpleNode: public InstructionNode, public Writer, public Reader {
		Type *type;
		Value *left, *right;
		SimpleNode(ASTNode *result_, ASTNode *type_, ASTNode *left_, ASTNode *right_);
		~SimpleNode();
		virtual const char * typeName() const = 0;
		virtual std::string debugExtra() const override;
		virtual std::vector<Value *> allValues() const override { return {left, right}; }
	};

	struct DivNode: public SimpleNode {
		enum class DivType {Sdiv, Udiv};
		DivType divType;
		DivNode(ASTNode *result_, ASTNode *div, ASTNode *type_, ASTNode *left_, ASTNode *right_);
		virtual const char * typeName() const override { return divType == DivType::Sdiv? "sdiv" : "udiv"; }
		virtual NodeType nodeType() const override { return NodeType::Div; }
	};

	struct RemNode: public SimpleNode {
		enum class RemType {Srem, Urem};
		RemType remType;
		RemNode(ASTNode *result_, ASTNode *rem, ASTNode *type_, ASTNode *left_, ASTNode *right_);
		virtual const char * typeName() const override { return remType == RemType::Srem? "srem" : "urem"; }
		virtual NodeType nodeType() const override { return NodeType::Rem; }
	};

	struct LogicNode: public SimpleNode {
		enum class LogicType {And, Or, Xor};
		LogicType logicType;
		LogicNode(ASTNode *result_, ASTNode *logic, ASTNode *type_, ASTNode *left_, ASTNode *right_);
		const char * typeName() const override;
		virtual NodeType nodeType() const override { return NodeType::Logic; }
	};

	struct ShrNode: public SimpleNode {
		enum class ShrType {Lshr, Ashr};
		ShrType shrType;
		ShrNode(ASTNode *result_, ASTNode *shr, ASTNode *type_, ASTNode *left_, ASTNode *right_);
		const char * typeName() const override { return shrType == ShrType::Lshr? "lshr" : "ashr"; }
		virtual NodeType nodeType() const override { return NodeType::Shr; }
	};

	struct FMathNode: public SimpleNode {
		enum class FMathType {Fadd, Fsub, Fmul, Fdiv, Frem};
		FMathType fmathType;
		std::unordered_set<Fastmath> fastmath;
		FMathNode(ASTNode *result_, ASTNode *fmath, ASTNode *flags, ASTNode *type_, ASTNode *left_, ASTNode *right_);
		const char * typeName() const override;
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::FMath; }
	};

	struct SwitchNode: public InstructionNode, public Reader {
		Type *type;
		Value *value;
		const std::string *label;
		std::vector<std::tuple<Type *, Value *, const std::string *>> table;

		SwitchNode(ASTNode *type_, ASTNode *value_, ASTNode *label_, ASTNode *table_);
		~SwitchNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Switch; }
		virtual std::vector<Value *> allValues() const override { return {value}; }
	};

	struct ExtractValueNode: public InstructionNode, public Writer, public Reader {
		Type *aggregateType;
		Value *aggregateValue;
		std::vector<int> decimals;
		ExtractValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value, ASTNode *decimals_);
		~ExtractValueNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::ExtractValue; }
		virtual std::vector<Value *> allValues() const override { return {aggregateValue}; }
	};

	struct InsertValueNode: public InstructionNode, public Writer, public Reader {
		Type *aggregateType, *type;
		Value *aggregateValue, *value;
		std::vector<int> decimals;
		InsertValueNode(ASTNode *result_, ASTNode *aggregate_type, ASTNode *aggregate_value, ASTNode *type_,
		                ASTNode *value_, ASTNode *decimals_);
		~InsertValueNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::InsertValue; }
		virtual std::vector<Value *> allValues() const override { return {aggregateValue, value}; }
	};

	struct ResumeNode: public InstructionNode, public Reader {
		Type *type;
		Value *value;
		ResumeNode(ASTNode *type_, ASTNode *value_);
		~ResumeNode();
		virtual std::string debugExtra() const override;
		virtual NodeType nodeType() const override { return NodeType::Resume; }
		virtual std::vector<Value *> allValues() const override { return {value}; }
	};
}

#endif
