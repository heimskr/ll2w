#include <iostream>
#include <sstream>

#include "parser/ASTNode.h"
#include "parser/Constant.h"
#include "parser/Lexer.h"

namespace LL2W {
	Constant::Constant(TypePtr type_, ValuePtr value_, const ParAttrs &parattrs_, Conversion conversion_,
	                   ConstantPtr conversion_source, TypePtr conversion_type):
		type(type_), value(value_), parattrs(parattrs_), conversion(conversion_),
		conversionSource(conversion_source), conversionType(conversion_type) {}

	Constant::Constant(const ASTNode *node) {
		if (node->symbol != CONSTANT)
			throw std::runtime_error("Constant::Constant: node doesn't have symbol CONSTANT");

		if (node->size() == 1) {
			// Just a GVAR here.
			type = getType(node->at(0));
			value = getValue(node->at(0));
		} else {
			type = getType(node->at(0));

			ASTNode *value_node = node->at(1);
			if (GetelementptrValue *gep_value = dynamic_cast<GetelementptrValue *>(value_node)) {
				value = gep_value->copy();
			} else if (value_node->symbol == CONVERSION_EXPR) {
				for (const std::pair<const Conversion, std::string> &pair: conversion_map) {
					if (*value_node->lexerInfo == pair.second) {
						conversion = pair.first;
						break;
					}
				}
				value = nullptr;
				conversionSource = std::make_shared<Constant>(value_node->at(0));
				conversionType = getType(value_node->at(1));
			} else {
				value = getValue(value_node);
			}

			if (2 < node->size())
				parattrs = {*node->at(2)};
		}
	}

	ConstantPtr Constant::copy() const {
		return std::make_shared<Constant>(type->copy(), value->copy(), parattrs, conversion,
			conversionSource? conversionSource->copy() : nullptr, conversionType? conversionType->copy() : nullptr);
	}

	Constant::operator std::string() const {
		std::stringstream out;
		out << std::string(*type);
		const std::string parattrs_str = parattrs;
		if (!parattrs_str.empty())
			out << " " << parattrs_str;
		if (value) {
			out << " " << std::string(*value);
		} else if (conversion != Conversion::None) {
			out << " \e[91m" << conversion_map.at(conversion) << "\e[0m \e[2m(\e[0m" << std::string(*conversionSource)
			    << " to " << std::string(*conversionType) << "\e[2m)\e[0m";
		}
		return out.str();
	}

	std::ostream & operator<<(std::ostream &os, const Constant &constant) {
		return os << std::string(constant);
	}
}