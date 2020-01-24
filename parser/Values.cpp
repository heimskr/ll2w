#include <iostream>
#include <sstream>

#include "ASTNode.h"
#include "Parser.h"
#include "Types.h"
#include "Values.h"
#include "Lexer.h"
#include "StringSet.h"

namespace LL2W {
	VectorValue::VectorValue(const ASTNode *node) {
		for (auto iter = node->cbegin(); iter != node->cend(); ++iter)
			values.push_back({getType((*iter)->at(0)), getValue((*iter)->at(1))});
	}

	VectorValue::~VectorValue() {
		for (const std::pair<Type *, Value *> &pair: values) {
			delete pair.first;
			delete pair.second;
		}
	}

	Value * VectorValue::copy() const {
		std::vector<std::pair<Type *, Value *>> newvec {};
		for (const std::pair<Type *, Value *> &pair: values)
			newvec.push_back({pair.first->copy(), pair.second->copy()});
		return new VectorValue(newvec);
	}

	VectorValue::operator std::string() {
		std::stringstream out;
		out << "\e[2m<\e[0m";
		auto begin = values.cbegin();
		for (auto iter = begin, end = values.cend(); iter != end; ++iter) {
			const std::pair<Type *, Value *> &pair = *iter;
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << std::string(*pair.first) << " " << std::string(*pair.second);
		}
		out << "\e[2m>\e[0m";
		return out.str();
	}

	LocalValue::LocalValue(const ASTNode *node) {
		name = node->lexerInfo->at(0) == '%'? StringSet::intern(node->lexerInfo->substr(1)) : node->lexerInfo;
	}

	GlobalValue::GlobalValue(const ASTNode *node) {
		name = node->lexerInfo->at(0) == '@'? StringSet::intern(node->lexerInfo->substr(1)) : node->lexerInfo;
	}

	GetelementptrValue::GetelementptrValue(bool inbounds_, Type *type_, Type *ptr_type, Value *variable_,
	                                       const std::vector<std::pair<int, long>> &decimals_):
		ASTNode(TOK_GETELEMENTPTR, ""), inbounds(inbounds_), type(type_), ptrType(ptr_type), variable(variable_),
		decimals(decimals_) {}

	GetelementptrValue::GetelementptrValue(const ASTNode *inbounds_, const ASTNode *type_, const ASTNode *ptr_type,
	                                       const ASTNode *variable_, const ASTNode *decimal_list):
	                                       ASTNode(TOK_GETELEMENTPTR, "") {
		if (inbounds_) {
			inbounds = true;
			delete inbounds_;
		}

		type = getType(type_);
		delete type_;

		ptrType = getType(ptr_type);
		delete ptr_type;

		variable = getValue(variable_);
		delete variable_;

		for (auto iter = decimal_list->cbegin(), end = decimal_list->cend(); iter != end; ++iter) {
			const ASTNode *comma = *iter;
			const ASTNode *inttype = comma->at(0);
			const ASTNode *decimal = comma->at(1);
			decimals.push_back({atoi(inttype->lexerInfo->substr(1).c_str()), atol(decimal->lexerInfo->c_str())});
		}
		delete decimal_list;
	}

	GetelementptrValue::GetelementptrValue(const ASTNode *node): ASTNode(TOK_GETELEMENTPTR, "") {
		node->debug();
		throw std::runtime_error("Unimplemented.");
	}

	GetelementptrValue::~GetelementptrValue() {
		delete type;
		delete ptrType;
		delete variable;
	}

	GetelementptrValue::operator std::string() {
		std::stringstream out;
		out << "\e[91mgetelementptr\e[0m";
		if (inbounds)
			out << " \e[91minbounds\e[0m";
		out << " \e[2m(\e[0m" << std::string(*type) << "\e[2m,\e[0m " << std::string(*ptrType) << " "
		    << std::string(*variable);
		for (const std::pair<int, long> &decimal: decimals)
			out << "\e[2m,\e[0m \e[33mi" << decimal.first << " \e[32m" << decimal.second << "\e[0m";
		out << "\e[2m)\e[0m";
		return out.str();
	}

	StructValue::StructValue(const ASTNode *node) {
		for (const ASTNode *comma: *node->at(0))
			values.push_back({getType(comma->at(0)), getValue(comma->at(1))});
	}

	StructValue::~StructValue() {
		for (const std::pair<Type *, Value *> &pair: values) {
			delete pair.first;
			delete pair.second;
		}
	}

	Value * StructValue::copy() const {
		std::vector<std::pair<Type *, Value *>> values_copy;
		for (const std::pair<Type *, Value *> &pair: values)
			values_copy.push_back({pair.first->copy(), pair.second->copy()});
		return new StructValue(std::move(values_copy));
	}

	StructValue::operator std::string() {
		std::stringstream out;
		out << "\e[2m{\e[0m";
		for (auto begin = values.cbegin(), iter = begin, end = values.cend(); iter != end; ++iter) {
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << std::string(*iter->first) << " " << std::string(*iter->second);
		}
		out << "\e[2m}\e[0m";
		return out.str();
	}

	ArrayValue::ArrayValue(const ASTNode *node) {
		for (const ASTNode *comma: *node) {
			if (comma->size() == 1) // Presumably just a GVAR rather than a type + value
				values.push_back({nullptr, getValue(comma->at(0))});
			else
				values.push_back({getType(comma->at(0)), getValue(comma->at(1))});
		}
	}

	ArrayValue::~ArrayValue() {
		for (const std::pair<Type *, Value *> &pair: values) {
			delete pair.first;
			delete pair.second;
		}
	}

	Value * ArrayValue::copy() const {
		std::vector<std::pair<Type *, Value *>> values_copy;
		values_copy.reserve(values.size());
		for (const std::pair<Type *, Value *> &pair: values)
			values_copy.push_back({pair.first->copy(), pair.second->copy()});
		return new ArrayValue(values_copy);
	}

	ArrayValue::operator std::string() {
		std::stringstream out;
		out << "\e[2m[\e[0m";
		for (auto begin = values.cbegin(), iter = begin, end = values.cend(); iter != end; ++iter) {
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			if (iter->first)
				out << std::string(*iter->first) << " ";
			out << std::string(*iter->second);
		}
		out << "\e[2m]\e[0m";
		return out.str();
	}

	Value * getValue(const ASTNode *node) {
		switch (node->symbol) {
			case TOK_FLOATING:      return new DoubleValue(node);
			case TOK_DECIMAL:       return new IntValue(node);
			case TOK_BOOL:          return new BoolValue(node);
			case VECTOR:            return new VectorValue(node);
			case TOK_PVAR:          return new LocalValue(node);
			case TOK_GVAR:          return new GlobalValue(node);
			case TOK_GETELEMENTPTR: return new GetelementptrValue(node);
			case TOK_VOID:          return new VoidValue();
			case STRUCT_VALUE:      return new StructValue(node);
			case VALUE_LIST:        return new ArrayValue(node);
			default: throw std::invalid_argument("Couldn't create Value from a node with symbol " +
			                                     std::string(Parser::getName(node->symbol)));
		}
	}
}
