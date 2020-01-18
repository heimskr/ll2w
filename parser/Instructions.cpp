#include <iostream>
#include <sstream>
#include "Instructions.h"

namespace LL2W {
	SelectNode::SelectNode(ASTNode *left_variable, ASTNode *fastmath_): leftVariable(left_variable->lexerInfo) {
		delete left_variable;
		for (ASTNode *child: *fastmath_) {
			const std::string &fmname = *child->lexerInfo;
			for (const std::pair<Fastmath, std::string> &pair: fastmath_map) {
				if (fmname == pair.second) {
					fastmath.insert(pair.first);
					break;
				}
			}
		}
	}
	
	std::string SelectNode::debugExtra() {
		std::stringstream out;
		out << "\e[32m" << *leftVariable << " \e[2m= \e[0;36mselect\e[0;38;5;202m";
		for (Fastmath flag: fastmath)
			out << " " << fastmath_map.at(flag);
		return out.str();
	}
}
