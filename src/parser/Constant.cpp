#include <iostream>
#include <sstream>

#include "parser/ASTNode.h"
#include "parser/Constant.h"
#include "parser/Lexer.h"
#include "util/Util.h"

namespace LL2W {
	Constant::Constant(TypePtr type_, ValuePtr value_, const ParAttrs &parattrs_, Conversion conversion_,
	                   ConstantPtr conversion_source, TypePtr conversion_type):
		type(type_), value(value_), parattrs(parattrs_), conversion(conversion_),
		conversionSource(conversion_source), conversionType(conversion_type) {}

	Constant::Constant(const ASTNode *node, TypePtr type_hint) {
		if (node->symbol == LLVMTOK_DECIMAL) {
			if (!type_hint)
				throw std::runtime_error("Constant::Constant: type hint expected for decimal node");
			type = type_hint;
			value = std::make_shared<IntValue>(node);
		} else if (node->symbol == LLVMTOK_NULL) {
			if (!type_hint)
				throw std::runtime_error("Constant::Constant: type hint expected for null node");
			type = type_hint;
			value = std::make_shared<NullValue>();
		} else if (node->symbol == LLVMTOK_PVAR) {
			if (!type_hint)
				throw std::runtime_error("Constant::Constant: type hint expected for pvar node");
			type = type_hint;
			value = std::make_shared<LocalValue>(node);
		} else if (node->symbol == LLVM_CONVERSION_EXPR) {
			// if (!type_hint)
			// 	throw std::runtime_error("Constant::Constant: type hint expected for conversion expression node");
			type = type_hint;
			value = nullptr;
			for (const std::pair<const Conversion, std::string> &pair: conversion_map)
				if (*node->lexerInfo == pair.second) {
					conversion = pair.first;
					break;
				}
			conversionSource = std::make_shared<Constant>(node->at(0));
			conversionType = getType(node->at(1));
		} else if (node->symbol != LLVM_CONSTANT) {
			node->debug();
			throw std::runtime_error("Constant::Constant: node doesn't have symbol LLVM_CONSTANT");
		} else if (node->size() == 1) {
			// Just a gvar here.
			type = getType(node->at(0));
			value = getValue(node->at(0));
		} else {
			type = getType(node->at(0));

			ASTNode *value_node = node->at(1);
			if (GetelementptrValue *gep_value = dynamic_cast<GetelementptrValue *>(value_node)) {
				value = gep_value->copy();
			} else if (value_node->symbol == LLVM_CONVERSION_EXPR) {
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
		return std::make_shared<Constant>(type? type->copy() : nullptr, value? value->copy() : nullptr, parattrs,
			conversion, conversionSource? conversionSource->copy() : nullptr,
			conversionType? conversionType->copy() : nullptr);
	}

	ConstantPtr Constant::convert() const {
		if (value)
			return copy();
		if (!conversionSource) {
			std::cerr << *this << "\n";
			throw std::runtime_error("Constant has neither a value nor a conversion source in Constant::convert()");
		}
		if (conversion != Conversion::Ptrtoint && conversion != Conversion::Inttoptr &&
		    conversion != Conversion::Bitcast) {
			std::cerr << *this << "\n";
			throw std::runtime_error("Unsupported conversion in Constant::convert(): " + conversion_map[conversion]);
		}
		if (!conversionSource->value) {
			// TODO: recursive conversion?
			std::cerr << *this << "\n";
			throw std::runtime_error("Conversion source has no value in Constant::convert()");
		}
		return std::make_shared<Constant>(conversionType->copy(), conversionSource->value->copy(), parattrs,
			Conversion::None, nullptr, nullptr);
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