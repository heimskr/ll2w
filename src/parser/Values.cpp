#include <iostream>
#include <sstream>

#include "compiler/Variable.h"
#include "parser/ASTNode.h"
#include "parser/Parser.h"
#include "parser/Types.h"
#include "parser/Values.h"
#include "parser/Lexer.h"
#include "parser/StringSet.h"
#include "parser/Constant.h"

namespace LL2W {
	bool Value::isInt() const {
		return valueType() == ValueType::Int;
	}

	bool Value::isBool() const {
		return valueType() == ValueType::Bool;
	}

	bool Value::isNull() const {
		return valueType() == ValueType::Null;
	}

	bool Value::isLocal() const {
		return valueType() == ValueType::Local;
	}

	bool Value::isGlobal() const {
		return valueType() == ValueType::Global;
	}

	bool Value::isGetelementptr() const {
		return valueType() == ValueType::Getelementptr;
	}

	VectorValue::VectorValue(const ASTNode *node) {
		for (auto iter = node->cbegin(); iter != node->cend(); ++iter)
			values.push_back({getType((*iter)->at(0)), getValue((*iter)->at(1))});
	}

	ValuePtr VectorValue::copy() const {
		std::vector<std::pair<TypePtr, ValuePtr>> newvec {};
		for (const std::pair<TypePtr, ValuePtr> &pair: values)
			newvec.push_back({pair.first->copy(), pair.second->copy()});
		return std::make_shared<VectorValue>(newvec);
	}

	VectorValue::operator std::string() {
		std::stringstream out;
		out << "\e[2m<\e[0m";
		auto begin = values.cbegin();
		for (auto iter = begin, end = values.cend(); iter != end; ++iter) {
			const std::pair<TypePtr, ValuePtr> &pair = *iter;
			if (iter != begin)
				out << "\e[2m,\e[0m ";
			out << std::string(*pair.first) << " " << std::string(*pair.second);
		}
		out << "\e[2m>\e[0m";
		return out.str();
	}

	LocalValue::LocalValue(const ASTNode *node): VariableValue(nullptr) {
		name = node->lexerInfo->at(0) == '%'? StringSet::intern(node->lexerInfo->substr(1)) : node->lexerInfo;
	}

	LocalValue::operator std::string() {
		return "\e[32m" + (variable? std::string(*variable) : "%" + *name) + "\e[39m";
	}

	GlobalValue::GlobalValue(const ASTNode *node): VariableValue(nullptr) {
		name = node->lexerInfo->at(0) == '@'? StringSet::intern(node->lexerInfo->substr(1)) : node->lexerInfo;
	}

	GetelementptrValue::GetelementptrValue(bool inbounds_, TypePtr type_, TypePtr ptr_type, ValuePtr variable_,
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
			constants.push_back(std::make_shared<Constant>(sub));
	}

	ValuePtr StructValue::copy() const {
		std::vector<std::shared_ptr<Constant>> constants_copy;
		for (ConstantPtr constant: constants)
			constants_copy.push_back(constant->copy());
		return std::make_shared<StructValue>(std::move(constants_copy));
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
			constants.push_back(std::make_shared<Constant>(sub));
	}

	ValuePtr ArrayValue::copy() const {
		std::vector<ConstantPtr> constants_copy;
		constants_copy.reserve(constants.size());
		for (ConstantPtr constant: constants)
			constants_copy.push_back(constant->copy());
		return std::make_shared<ArrayValue>(constants_copy);
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

	ValuePtr getValue(ASTNode *node) {
		switch (node->symbol) {
			case TOK_FLOATING:        return std::make_shared<DoubleValue>(node);
			case TOK_DECIMAL:         return std::make_shared<IntValue>(node);
			case TOK_BOOL:            return std::make_shared<BoolValue>(node);
			case VECTOR:              return std::make_shared<VectorValue>(node);
			case TOK_PVAR:            return std::make_shared<LocalValue>(node);
			case TOK_GVAR:            return std::make_shared<GlobalValue>(node);
			case TOK_GETELEMENTPTR:   return std::make_shared<GetelementptrValue>(node);
			case TOK_VOID:            return std::make_shared<VoidValue>();
			case STRUCT_VALUE:        return std::make_shared<StructValue>(node);
			case VALUE_LIST:          return std::make_shared<ArrayValue>(node);
			case TOK_NULL:            return std::make_shared<NullValue>();
			case TOK_CSTRING:         return std::make_shared<CStringValue>(node);
			case TOK_ZEROINITIALIZER: return std::make_shared<ZeroinitializerValue>();
			case TOK_UNDEF:           return std::make_shared<UndefValue>();
			default: throw std::invalid_argument("Couldn't create Value from a node with symbol " +
			                                     std::string(Parser::getName(node->symbol)));
		}
	}

	std::ostream & operator<<(std::ostream &os, Value &value) {
		return os << std::string(value);
	}
}
