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
	struct InstructionNode: public ASTNode {
		InstructionNode(const std::string *str): ASTNode(INSTRUCTION, str) {}
		InstructionNode(): ASTNode(INSTRUCTION, "") {}
		virtual std::string style() const override { return "\e[36m"; }
	};

	struct SelectNode: public InstructionNode {
		const std::string *result;
		std::unordered_set<Fastmath> fastmath;
		Type *conditionType, *firstType, *secondType;
		Value *conditionValue, *firstValue, *secondValue;

		SelectNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *condition_type, ASTNode *condition_value,
		           ASTNode *type1, ASTNode *val1, ASTNode *type2, ASTNode *val2);
		~SelectNode();
		virtual std::string debugExtra() const override;
	};

	struct AllocaNode: public InstructionNode {
		const std::string *result;
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
	};

	struct StoreNode: public InstructionNode {
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
	};

	struct LoadNode: public InstructionNode {
		const std::string *result;
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
	};

	struct IcmpNode: public InstructionNode {
		const std::string *result;
		IcmpCond cond;
		Type *type;
		Value *value1, *value2;

		IcmpNode(ASTNode *result_, ASTNode *cond_, ASTNode *type_, ASTNode *op1, ASTNode *op2);
		~IcmpNode();
		virtual std::string debugExtra() const override;
	};

	struct BrUncondNode: public InstructionNode {
		const std::string *destination;
		BrUncondNode(const std::string *destination_): destination(destination_) {}
		BrUncondNode(const std::string &destination_): BrUncondNode(&destination_) {}
		BrUncondNode(const ASTNode *node): BrUncondNode(node->lexerInfo) { delete node; }
		virtual std::string debugExtra() const override;
	};

	struct BrCondNode: public InstructionNode {
		Value *condition;
		const std::string *ifTrue, *ifFalse;

		BrCondNode(ASTNode *type, ASTNode *condition_, ASTNode *if_true, ASTNode *if_false);
		~BrCondNode();
		virtual std::string debugExtra() const override;
	};

	class CallInvokeNode: public InstructionNode {
		protected:
			CallInvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace,
			               ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
			               ASTNode *attribute_list);

		public:
			const std::string *result = nullptr, *cconv = nullptr;
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
	};

	struct CallNode: public CallInvokeNode {
		const std::string *tail = nullptr;
		std::unordered_set<Fastmath> fastmath;

		CallNode(ASTNode *_result, ASTNode *_tail, ASTNode *fastmath_flags, ASTNode *_cconv, ASTNode *_retattrs,
		         ASTNode *_addrspace, ASTNode *return_type, ASTNode *_args, ASTNode *function_name, ASTNode *_constants,
		         ASTNode *attribute_list);
		virtual std::string debugExtra() const override;
	};

	struct InvokeNode: public CallInvokeNode {
		const std::string *normalLabel, *exceptionLabel;

		InvokeNode(ASTNode *_result, ASTNode *_cconv, ASTNode *_retattrs, ASTNode *_addrspace, ASTNode *return_type,
		           ASTNode *_args, ASTNode *function_name, ASTNode *_constants, ASTNode *attribute_list,
		           ASTNode *normal_label, ASTNode *exception_label);
		virtual std::string debugExtra() const override;
	};

	struct GetelementptrNode: public InstructionNode {
		const std::string *result, *ptrValue;
		bool inbounds = false;
		Type *type, *ptrType;
		std::vector<std::tuple<int, int, bool>> indices;

		GetelementptrNode(ASTNode *pvar, ASTNode *_inbounds, ASTNode *type_, ASTNode *ptr_type, ASTNode *ptrval,
		                  ASTNode *indices_);
		~GetelementptrNode();
		virtual std::string debugExtra() const override;
	};

	struct RetNode: public InstructionNode {
		Type *type;
		Value *value;

		RetNode();
		RetNode(ASTNode *type_, ASTNode *value_);
		~RetNode();
		virtual std::string debugExtra() const override;
	};

	struct LandingpadNode: public InstructionNode {
		struct Clause {
			enum class ClauseType {Catch, Filter};
			ClauseType clauseType;
			Type *type = nullptr;
			Value *value = nullptr;
			Clause(ASTNode *);
			~Clause();
			operator std::string() const;
		};

		const std::string *result;
		Type *type;
		bool cleanup;
		std::vector<Clause *> clauses;

		LandingpadNode(ASTNode *result_, ASTNode *type_, ASTNode *clauses_, bool cleanup_);
		~LandingpadNode();
		virtual std::string debugExtra() const override;
	};

	struct ConversionNode: public InstructionNode {
		const std::string *result;
		Type *from, *to;
		Value *value;
		Conversion conversionType;
		ConversionNode(ASTNode *result_, ASTNode *conv_op, ASTNode *from_, ASTNode *value_, ASTNode *to_);
		~ConversionNode();
		virtual std::string debugExtra() const override;
	};

	struct BasicMathNode: public InstructionNode {
		const std::string *result;
		const std::string *oper;
		int operSymbol;
		bool nuw = false, nsw = false;
		Type *type;
		Value *left, *right;
		BasicMathNode(ASTNode *result_, ASTNode *oper_, bool nuw_, bool nsw_, ASTNode *type_, ASTNode *left_,
		              ASTNode *right_);
		~BasicMathNode();
		virtual std::string debugExtra() const override;
	};

	struct PhiNode: public InstructionNode {
		const std::string *result;
		std::unordered_set<Fastmath> fastmath;
		Type *type;
		std::vector<std::pair<Value *, const std::string *>> pairs;
		PhiNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *type_, ASTNode *pairs_);
		~PhiNode();
		virtual std::string debugExtra() const override;
	};

	struct SimpleNode: public InstructionNode {
		const std::string *result;
		Type *type;
		Value *left, *right;
		SimpleNode(ASTNode *result_, ASTNode *type_, ASTNode *left_, ASTNode *right_);
		~SimpleNode();
		virtual const char * typeName() const = 0;
		virtual std::string debugExtra() const override;
	};

	struct DivNode: public SimpleNode {
		enum class DivType {Sdiv, Udiv};
		DivType divType;
		DivNode(ASTNode *result_, ASTNode *div, ASTNode *type_, ASTNode *left_, ASTNode *right_);
		virtual const char * typeName() const { return divType == DivType::Sdiv? "sdiv" : "udiv"; }
	};

	struct RemNode: public SimpleNode {
		enum class RemType {Srem, Urem};
		RemType remType;
		RemNode(ASTNode *result_, ASTNode *rem, ASTNode *type_, ASTNode *left_, ASTNode *right_);
		virtual const char * typeName() const { return remType == RemType::Srem? "srem" : "urem"; }
	};

	struct LogicNode: public SimpleNode {
		enum class LogicType {And, Or, Xor};
		LogicType logicType;
		LogicNode(ASTNode *result_, ASTNode *logic, ASTNode *type_, ASTNode *left_, ASTNode *right_);
		const char * typeName() const override;
	};
}

#endif
