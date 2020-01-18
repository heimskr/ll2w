#include <iostream>
#include <sstream>

#include "Instructions.h"

namespace LL2W {
	SelectNode::SelectNode(ASTNode *left_variable, ASTNode *fastmath_, ASTNode *condition_type,
	                       ASTNode *condition_value, ASTNode *type1, ASTNode *val1, ASTNode *type2, ASTNode *val2):
	                       leftVariable(left_variable->lexerInfo), conditionValue(condition_value) {
		leftVariable = left_variable->lexerInfo;
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
		delete fastmath_;

		conditionType = getType(condition_type);
		delete condition_type;

		conditionValue = condition_value;

		firstType = getType(type1);
		delete type1;

		firstValue = val1;

		secondType = getType(type2);
		delete type2;

		secondValue = val2;

		adopt(val1);
		adopt(val2);
	}
	
	std::string SelectNode::debugExtra() {
		std::stringstream out;
		out << "\e[32m" << *leftVariable << " \e[2m= \e[0;36mselect\e[0;38;5;202m";
		for (Fastmath flag: fastmath)
			out << " " << fastmath_map.at(flag);
		out << " \e[33m" << std::string(*conditionType) << " \e[0m" << conditionValue->concatenate() << ", \e[33m";
		out << std::string(*firstType) << " \e[0m" << firstValue->concatenate() << ", \e[33m";
		out << std::string(*secondType) << " \e[0m" << secondValue->concatenate();
		return out.str();
	}
}
