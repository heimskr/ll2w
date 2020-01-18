#ifndef PARSER_INSTRUCTIONS_H_
#define PARSER_INSTRUCTIONS_H_

#include <unordered_set>

#include "ASTNode.h"
#include "Enums.h"
#include "Types.h"
#include "Values.h"
#include "Lexer.h"

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
		virtual std::string debugExtra() override;
	};

	struct AllocaNode: public InstructionNode {
		const std::string *result;
		bool inalloca = false;
		Type *type;
		Type *numelementsType = nullptr;
		Value *numelementsValue = nullptr;
		int align = -1;

		AllocaNode(ASTNode *result_, ASTNode *inalloca_, ASTNode *type_, ASTNode *numelements_, ASTNode *align_,
		           ASTNode *addrspace_);
		~AllocaNode();
		virtual std::string debugExtra() override;
	};
}

#endif
