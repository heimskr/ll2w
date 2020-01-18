#ifndef PARSER_INSTRUCTIONS_H_
#define PARSER_INSTRUCTIONS_H_

#include "ASTNode.h"
#include "yyparse.h"

namespace LL2W {
	struct InstructionNode: public ASTNode {
		InstructionNode(const std::string *str): ASTNode(INSTRUCTION, str) {}
		InstructionNode(): ASTNode(INSTRUCTION, "") {}
	};

	struct SelectNode: public InstructionNode {
		const std::string *leftVariable;

		SelectNode(ASTNode *left_variable): leftVariable(left_variable->lexerInfo) {}
	};
}

#endif
