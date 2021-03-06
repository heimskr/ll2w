#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <unordered_map>

#include "compiler/Function.h"
#include "compiler/Variable.h"
#include "parser/ASTNode.h"
#include "parser/Parser.h"
#include "parser/Types.h"
#include "parser/Values.h"
#include "parser/Lexer.h"
#include "parser/StringSet.h"
#include "parser/Constant.h"
#include "util/Util.h"

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

	int Value::intValue() {
		long val = longValue();
		if (INT_MAX < val)
			warn() << "Value " << val << " is larger than INT_MAX\n";
		return static_cast<int>(val);
	}

	IntValue::IntValue(const std::string &value_) {
		value = Util::parseLong(value_, value_.substr(0, 2) == "0x"? 16 : 10);
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

	LocalValue::LocalValue(std::shared_ptr<Variable> variable_):
		VariableValue(StringSet::intern(std::to_string(variable_->id))), variable(variable_) {}

	LocalValue::LocalValue(const ASTNode *node): VariableValue(nullptr) {
		name = node->lexerInfo->at(0) == '%'? StringSet::intern(node->lexerInfo->substr(1)) : node->lexerInfo;
	}

	LocalValue::operator std::string() {
		return "\e[32m" + (variable? std::string(*variable) : "%" + *name) + "\e[39m";
	}

	std::shared_ptr<Variable> LocalValue::getVariable(Function &function) {
		if (variable)
			return variable;
		return function.getVariable(*name);
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

	std::string CStringValue::reescape() const {
		std::string out;
		for (int i = 0, max = value->length() - 2; i < max; ++i) {
			const char ch0 = (*value)[i], ch1 = (*value)[i + 1], ch2 = (*value)[i + 2];
			if (ch0 == '\\' && Util::isHex(ch1) && Util::isHex(ch2)) {
				out += std::string("\\x") + ch1 + ch2;
				i += 2;
			} else {
				out += ch0;
			}
		}
		return out;
	}

	ValuePtr getValue(ASTNode *node) {
		switch (node->symbol) {
			case LLVMTOK_FLOATING:        return std::make_shared<DoubleValue>(node);
			case LLVMTOK_DECIMAL:         return std::make_shared<IntValue>(node);
			case LLVMTOK_HEXADECIMAL:     return std::make_shared<IntValue>(node);
			case LLVMTOK_BOOL:            return std::make_shared<BoolValue>(node);
			case LLVM_VECTOR:             return std::make_shared<VectorValue>(node);
			case LLVMTOK_PVAR:            return std::make_shared<LocalValue>(node);
			case LLVMTOK_GVAR:            return std::make_shared<GlobalValue>(node);
			case LLVMTOK_GETELEMENTPTR:   return std::make_shared<GetelementptrValue>(node);
			case LLVMTOK_VOID:            return std::make_shared<VoidValue>();
			case LLVM_STRUCT_VALUE:       return std::make_shared<StructValue>(node);
			case LLVM_VALUE_LIST:         return std::make_shared<ArrayValue>(node);
			case LLVMTOK_NULL:            return std::make_shared<NullValue>();
			case LLVMTOK_CSTRING:         return std::make_shared<CStringValue>(node);
			case LLVMTOK_ZEROINITIALIZER: return std::make_shared<ZeroinitializerValue>();
			case LLVMTOK_UNDEF:           return std::make_shared<UndefValue>();
			case LLVM_CONVERSION_EXPR:    return convertConversion(node);
			default:
				node->debug();
				throw std::invalid_argument("Couldn't create Value from a node with symbol " +
			                                std::string(llvmParser.getName(node->symbol)));
		}
	}

	ValuePtr convertConversion(ASTNode *node) {
		// TODO: verify
		if (node->at(0)->symbol == LLVM_CONSTANT)
			return Constant(node->at(0)).convert()->value;
		return getValue(node->at(0));
	}

	std::ostream & operator<<(std::ostream &os, Value &value) {
		return os << std::string(value);
	}

	static std::unordered_map<ValueType, std::string> value_names {
		{ValueType::Double, "Double"}, {ValueType::Int, "Int"}, {ValueType::Null, "Null"},
		{ValueType::Vector, "Vector"}, {ValueType::Bool, "Bool"}, {ValueType::Local, "Local"},
		{ValueType::Global, "Global"}, {ValueType::Getelementptr, "Getelementptr"}, {ValueType::Void, "Void"},
		{ValueType::Struct, "Struct"}, {ValueType::Array, "Array"}, {ValueType::CString, "CString"},
		{ValueType::Zeroinitializer, "Zeroinitializer"}, {ValueType::Undef, "Undef"},
	};

	std::string getName(ValueType type) {
		return value_names.at(type);
	}
}
