#include <iostream>
#include <sstream>

#include "Instructions.h"

namespace LL2W {
	SelectNode::SelectNode(ASTNode *result_, ASTNode *fastmath_, ASTNode *condition_type,
	                       ASTNode *condition_value, ASTNode *type1, ASTNode *val1, ASTNode *type2, ASTNode *val2) {
		result = result_->lexerInfo;
		delete result_;

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

		conditionValue = getValue(condition_value);
		delete condition_value;

		firstType = getType(type1);
		delete type1;

		firstValue = getValue(val1);
		delete val1;

		secondType = getType(type2);
		delete type2;

		secondValue = getValue(val2);
		delete val2;
	}
	
	std::string SelectNode::debugExtra() {
		std::stringstream out;
		out << "\e[32m" << *result << " \e[2m= \e[0;36mselect\e[0;38;5;202m";
		for (Fastmath flag: fastmath)
			out << " " << fastmath_map.at(flag);
		out << " " << std::string(*conditionType) << " " << std::string(*conditionValue) << ", "
		    << std::string(*firstType) << " " << std::string(*firstValue) << ", " << std::string(*secondType)
		    << " " << std::string(*secondValue);
		return out.str();
	}

	AllocaNode::AllocaNode(ASTNode *result_, ASTNode *inalloca_) {
		result = result_->lexerInfo;
		delete result_;

		if (inalloca_) {
			inalloca = true;
			delete inalloca_;
		}
	}
}
