#include <iostream>
#include "Instructions.h"

namespace LL2W {
	SelectNode::SelectNode(ASTNode *left_variable, ASTNode *fastmath): leftVariable(left_variable->lexerInfo) {
		delete left_variable;
		adopt(fastmath);
	}
	
	std::string SelectNode::debugExtra() {
		return "\e[32m" + *leftVariable + " \e[2m= \e[0;36mselect";
	}
}
