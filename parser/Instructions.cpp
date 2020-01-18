#include <iostream>
#include <sstream>

#include "Instructions.h"

namespace LL2W {
	SelectNode::SelectNode(ASTNode *left_variable, ASTNode *fastmath_, ASTNode *condition_type,
	                       ASTNode *condition_value):
	                       leftVariable(left_variable->lexerInfo), conditionValue(condition_value) {
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

		conditionType = getType(condition_type);
		delete condition_type;
	}
	
	std::string SelectNode::debugExtra() {
		std::stringstream out;
		out << "\e[32m" << *leftVariable << " \e[2m= \e[0;36mselect\e[0;38;5;202m";
		for (Fastmath flag: fastmath)
			out << " " << fastmath_map.at(flag);
		out << " \e[33m" << std::string(*conditionType) << " \e[0;1m" << *conditionValue->lexerInfo;
		out << "\e[0m";
		return out.str();
	}
}
