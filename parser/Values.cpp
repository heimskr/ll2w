#include <iostream>
#include <sstream>

#include "ASTNode.h"
#include "Parser.h"
#include "Types.h"
#include "Values.h"
#include "Lexer.h"
#include "StringSet.h"
#include "Constant.h"

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
		inbounds(inbounds_), type(type_), ptrType(ptr_type), variable(variable_), decimals(decimals_) {}

	GetelementptrValue::GetelementptrValue(ASTNode *inbounds_, ASTNode *type_, ASTNode *ptr_type, ASTNode *variable_,
	                                       ASTNode *decimal_list) {
		type = getType(type_);
		ptrType = getType(ptr_type);
		variable = getValue(variable_);
		for (auto iter = decimal_list->cbegin(), end = decimal_list->cend(); iter != end; ++iter) {
			const ASTNode *comma = *iter;
			const ASTNode *inttype = comma->at(0);
			const ASTNode *decimal = comma->at(1);
			decimals.push_back({atoi(inttype->lexerInfo->substr(1).c_str()), atol(decimal->lexerInfo->c_str())});
		}

		delete type_;
		delete ptr_type;
		delete variable_;
		delete decimal_list;

		if (inbounds_) {
			inbounds = true;
			delete inbounds_;
		}
	}

	GetelementptrValue::GetelementptrValue(ASTNode *node) {
		inbounds = node->size() == 5;
		type = getType(node->at(0));
		ptrType = getType(node->at(1));
		variable = getValue(node->at(2));

		for (auto iter = node->at(3)->cbegin(), end = node->at(3)->cend(); iter != end; ++iter) {
			const ASTNode *comma = *iter;
			const ASTNode *inttype = comma->at(0);
			const ASTNode *decimal = comma->at(1);
			decimals.push_back({atoi(inttype->lexerInfo->substr(1).c_str()), atol(decimal->lexerInfo->c_str())});
		}
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
		for (const ASTNode *sub: *node->at(0))
			constants.push_back(new Constant(sub));
	}

	StructValue::~StructValue() {
		for (Constant *constant: constants)
			delete constant;
	}

	Value * StructValue::copy() const {
		std::vector<Constant *> constants_copy;
		for (const Constant *constant: constants)
			constants_copy.push_back(constant->copy());
		return new StructValue(std::move(constants_copy));
	}

	StructValue::operator std::string() {
		std::stringstream out;
		out << "\e[2m{\e[0m";
		for (auto begin = constants.cbegin(), iter = begin, end = constants.cend(); iter != end; ++iter) {
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << std::string(**iter);
		}
		out << "\e[2m}\e[0m";
		return out.str();
	}

	ArrayValue::ArrayValue(const ASTNode *node) {
		for (const ASTNode *sub: *node)
			constants.push_back(new Constant(sub));
	}

	ArrayValue::~ArrayValue() {
		for (Constant *constant: constants)
			delete constant;
	}

	Value * ArrayValue::copy() const {
		std::vector<Constant *> constants_copy;
		constants_copy.reserve(constants.size());
		for (const Constant *constant: constants)
			constants_copy.push_back(constant->copy());
		return new ArrayValue(constants_copy);
	}

	ArrayValue::operator std::string() {
		std::stringstream out;
		out << "\e[2m[\e[0m";
		for (auto begin = constants.cbegin(), iter = begin, end = constants.cend(); iter != end; ++iter) {
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << std::string(**iter);
		}
		out << "\e[2m]\e[0m";
		return out.str();
	}

	CStringValue::CStringValue(const ASTNode *node): CStringValue(StringSet::intern(node->extractName())) {}

	Value * getValue(ASTNode *node) {
		switch (node->symbol) {
			case TOK_FLOATING:        return new DoubleValue(node);
			case TOK_DECIMAL:         return new IntValue(node);
			case TOK_BOOL:            return new BoolValue(node);
			case VECTOR:              return new VectorValue(node);
			case TOK_PVAR:            return new LocalValue(node);
			case TOK_GVAR:            return new GlobalValue(node);
			case TOK_GETELEMENTPTR:   return new GetelementptrValue(node);
			case TOK_VOID:            return new VoidValue();
			case STRUCT_VALUE:        return new StructValue(node);
			case VALUE_LIST:          return new ArrayValue(node);
			case TOK_NULL:            return new NullValue();
			case TOK_CSTRING:         return new CStringValue(node);
			case TOK_ZEROINITIALIZER: return new ZeroinitializerValue();
			default: throw std::invalid_argument("Couldn't create Value from a node with symbol " +
			                                     std::string(Parser::getName(node->symbol)));
		}
	}

	std::ostream & operator<<(std::ostream &os, Value &value) {
		return os << std::string(value);
	}
}
