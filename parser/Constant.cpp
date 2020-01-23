#include <iostream>
#include <sstream>

#include "ASTNode.h"
#include "Constant.h"
#include "Lexer.h"

namespace LL2W {
	Constant::Constant(ASTNode *node) {
		if (node->symbol != CONSTANT)
			throw std::runtime_error("Constant::Constant: node doesn't have symbol CONSTANT");
		type = getType(node->at(0));

		ASTNode *value_node = node->at(2);
		if (GetelementptrValue *gep_value = dynamic_cast<GetelementptrValue *>(value_node)) {
			value = gep_value->copy();
		} else if (value_node->symbol == CONST_EXPR) {
			for (const std::pair<Conversion, std::string> &pair: conversion_map) {
				if (*value_node->lexerInfo == pair.second) {
					conversion = pair.first;
					break;
				}
			}
			value = nullptr;
			conversionSource = new Constant(value_node->at(0));
			conversionType = getType(value_node->at(1));
		} else {
			value = getValue(value_node);
		}

		for (ASTNode *child: *node->at(1)) {
			if (child->symbol == TOK_DEREF) {
				dereferenceable = atoi(child->at(0)->lexerInfo->c_str());
			} else {
				for (const std::pair<ParAttr, std::string> &pair: parattr_map) {
					if (*child->lexerInfo == pair.second) {
						parattrs.insert(pair.first);
						break;
					}
				}
			}
		}
	}

	Constant::~Constant() {
		delete type;
		delete value;
		if (conversionSource)
			delete conversionSource;
		if (conversionType)
			delete conversionType;
	}

	Constant::operator std::string() const {
		std::stringstream out;
		out << std::string(*type);
		for (ParAttr attr: parattrs)
			out << " " << parattr_map.at(attr);
		if (dereferenceable != -1)
			out << " \e[34mdereferenceable\e[0;2m(\e[0m" << dereferenceable << "\e[2m)\e[0m";
		if (value) {
			out << " " << std::string(*value);
		} else if (conversion != Conversion::None) {
			out << " \e[91m" << conversion_map.at(conversion) << "\e[0m \e[2m(\e[0m" << std::string(*conversionSource)
			    << " to " << std::string(*conversionType) << "\e[2m)\e[0m";
		}
		return out.str();
	}
}