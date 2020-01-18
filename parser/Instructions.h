#ifndef PARSER_INSTRUCTIONS_H_
#define PARSER_INSTRUCTIONS_H_

#include <unordered_set>

#include "ASTNode.h"
#include "Enums.h"
#include "yyparse.h"

namespace LL2W {
	struct InstructionNode: public ASTNode {
		InstructionNode(const std::string *str): ASTNode(INSTRUCTION, str) {}
		InstructionNode(): ASTNode(INSTRUCTION, "") {}
		virtual std::string style() const override { return "\e[36m"; }
	};

	struct SelectNode: public InstructionNode {
		const std::string *leftVariable;
		std::unordered_set<Fastmath> fastmath;

		SelectNode(ASTNode *left_variable, ASTNode *fastmath_);
		virtual std::string debugExtra() override;
	};
}

#endif
