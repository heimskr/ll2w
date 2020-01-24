#include <iostream>
#include <sstream>

#include "ASTNode.h"
#include "Constant.h"
#include "Lexer.h"

namespace LL2W {
	Constant::Constant(Type *type_, Value *value_, const ParAttrs &parattrs_, Conversion conversion_,
	                   Constant *conversion_source, Type *conversion_type):
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

			parattrs = {*node->at(1)};
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

	Constant * Constant::copy() const {
		return new Constant(type->copy(), value->copy(), parattrs, conversion,
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
}