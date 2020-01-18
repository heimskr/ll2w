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

	SelectNode::~SelectNode() {
		delete result;
		delete conditionType;
		delete conditionValue;
		delete firstType;
		delete firstValue;
		delete secondType;
		delete secondValue;
	}

	std::string SelectNode::debugExtra() {
		std::stringstream out;
		out << "\e[32m" << *result << " \e[2m= \e[0;36mselect\e[0;38;5;202m";
		for (Fastmath flag: fastmath)
			out << " " << fastmath_map.at(flag);
		out << " " << std::string(*conditionType) << " " << std::string(*conditionValue) << "\e[2m,\e[0m "
		    << std::string(*firstType) << " " << std::string(*firstValue) << "\e[2m,\e[0m " << std::string(*secondType)
		    << " " << std::string(*secondValue);
		return out.str();
	}

	AllocaNode::AllocaNode(ASTNode *result_, ASTNode *inalloca_, ASTNode *type_, ASTNode *numelements_) {
		result = result_->lexerInfo;
		delete result_;

		if (inalloca_) {
			inalloca = true;
			delete inalloca_;
		}

		type = getType(type_);
		delete type_;

		// numelements_ is expected to be a TOK_COMMA node with a type_any child and a TOK_DECIMAL child.
		if (numelements_) {
			numelementsType = getType(numelements_->at(0));
			numelementsValue = getValue(numelements_->at(1));
			delete numelements_;
		}
	}

	AllocaNode::~AllocaNode() {
		delete result;
		delete type;
		if (numelementsType) delete numelementsType;
		if (numelementsValue) delete numelementsValue;
	}

	std::string AllocaNode::debugExtra() {
		std::stringstream out;
		out << "\e[32m" << *result << "\e[0;2m = \e[0;36malloca\e[0m";
		if (inalloca)
			out << " \e[38;5;202minalloca\e[0m";
		if (numelementsType)
			out << "\e[2m,\e[0m " << std::string(*numelementsType) << " " << std::string(*numelementsValue);

		return out.str();
	}
}
