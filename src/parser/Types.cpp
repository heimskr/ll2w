#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include "parser/ASTNode.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "parser/Types.h"
#include "parser/StructNode.h"

namespace LL2W {
	IntType::operator std::string() {
		return "\e[33mi" + std::to_string(intWidth) + "\e[0m";
	}

	bool IntType::operator==(const Type &other) const {
		return other.typeType() == TypeType::Int && dynamic_cast<const IntType &>(other).intWidth == intWidth;
	}

	ArrayType::operator std::string() {
		return "\e[2m[\e[0m" + std::to_string(count) + " \e[2mx\e[0m " + std::string(*subtype) + "\e[2m]\e[0m";
	}

	bool ArrayType::operator==(const Type &other) const {
		if (other.typeType() != TypeType::Array)
			return false;
		if (const ArrayType *otherArray = dynamic_cast<const ArrayType *>(&other))
			return count == otherArray->count && *otherArray->subtype == *subtype;
		return false;
	}

	VectorType::operator std::string() {
		return "\e[2m<\e[0m" + std::to_string(this->count) + " \e[2mx\e[0m " + std::string(*this->subtype) + "\e[2m>\e[0m";
	}

	bool VectorType::operator==(const Type &other) const {
		if (other.typeType() != TypeType::Vector)
			return false;
		if (const VectorType *otherVector = dynamic_cast<const VectorType *>(&other))
			return count == otherVector->count && *otherVector->subtype == *subtype;
		return false;
	}

	FloatType::operator std::string() {
		switch (type) {
			case FloatType::Type::Half: return "half";
			case FloatType::Type::Float: return "float";
			case FloatType::Type::Double: return "double";
			case FloatType::Type::FP128: return "fp128";
			case FloatType::Type::x86_FP80: return "x86_fp80";
			case FloatType::Type::PPC_FP128: return "ppc_fp128";
			default: throw std::runtime_error("Unrecognized float type: " + std::to_string(static_cast<int>(type)));
		}
	}

	FloatType::Type FloatType::getType(const std::string &str) {
		if (str == "half") return FloatType::Type::Half;
		else if (str == "float") return FloatType::Type::Float;
		else if (str == "double") return FloatType::Type::Double;
		else if (str == "fp128") return FloatType::Type::FP128;
		else if (str == "x86_fp80") return FloatType::Type::x86_FP80;
		else if (str == "ppc_fp128") return FloatType::Type::PPC_FP128;
		throw std::invalid_argument("Unknown float type: " + str);
	}

	int FloatType::width() const {
		switch (type) {
			case FloatType::Type::Half:   return WhyInfo::halfFloatWidth;
			case FloatType::Type::Float:  return WhyInfo::floatWidth;
			case FloatType::Type::Double: return WhyInfo::doubleWidth;
			default: return WhyInfo::doubleWidth;
		}
	}

	bool FloatType::operator==(const LL2W::Type &other) const {
		return other.typeType() == TypeType::Float && dynamic_cast<const FloatType &>(other).type == type;
	}

	PointerType::operator std::string() {
		return std::string(*subtype) + "\e[1;2m*\e[0m";
	}

	bool PointerType::operator==(const Type &other) const {
		return other.typeType() == TypeType::Pointer && *dynamic_cast<const PointerType &>(other).subtype == *subtype;
	}

	FunctionType::FunctionType(const ASTNode *node) {
		returnType = getType(node->at(0));
		if (node->children.size() == 3 || (1 < node->size() && node->at(1)->symbol == TYPE_LIST)) {
			ASTNode *list = node->at(1);
			argumentTypes.reserve(list->children.size());
			for (ASTNode *child: *list)
				argumentTypes.push_back(getType(child));
		}

		ellipsis = node->size() == 3 || (1 < node->size() && node->at(1)->symbol == TOK_ELLIPSIS);
	}

	FunctionType::~FunctionType() {
		delete returnType;
		for (Type *argumentType: argumentTypes)
			delete argumentType;
	}

	FunctionType::operator std::string() {
		if (!cached.empty())
			return cached;

		std::stringstream out;
		out << std::string(*returnType) << " (";

		if (!argumentTypes.empty()) {
			for (size_t i = 0, l = argumentTypes.size(); i < l; ++i) {
				if (i)
					out << ", ";
				out << std::string(*argumentTypes.at(i));
			}

			if (ellipsis)
				out << ", ...";
		} else if (ellipsis) {
			out << "...";
		}

		out << ") *";
		return cached = out.str();
	}

	Type * FunctionType::copy() const {
		std::vector<Type *> argument_types {};
		for (Type *argument_type: argumentTypes)
			argument_types.push_back(argument_type->copy());
		return new FunctionType(returnType->copy(), argument_types);
	}

	bool FunctionType::operator==(const Type &other) const {
		if (other.typeType() != TypeType::Function)
			return false;
		const FunctionType &otherFunction = dynamic_cast<const FunctionType &>(other);
		if (ellipsis != otherFunction.ellipsis || argumentTypes.size() != otherFunction.argumentTypes.size())
			return false;
		if (*returnType != *otherFunction.returnType)
			return false;
		for (size_t i = 0, size = argumentTypes.size(); i < size; ++i) {
			if (*argumentTypes[i] != *otherFunction.argumentTypes[i])
				return false;
		}
		return true;
	}

	bool FunctionType::operator!=(const Type &other) const {
		if (other.typeType() != TypeType::Function)
			return true;
		const FunctionType &otherFunction = dynamic_cast<const FunctionType &>(other);
		if (ellipsis != otherFunction.ellipsis || argumentTypes.size() != otherFunction.argumentTypes.size())
			return true;
		if (*returnType != *otherFunction.returnType)
			return true;
		for (size_t i = 0, size = argumentTypes.size(); i < size; ++i) {
			if (*argumentTypes[i] != *otherFunction.argumentTypes[i])
				return true;
		}
		return false;
	}

	std::unordered_map<std::string, std::shared_ptr<StructType>> StructType::knownStructs = {};

	StructType::StructType(const StructNode *node_):
		name(node_->name), form(node_->form), shape(node_->shape), node(node_->copy()) {}

	StructType::~StructType() {
		delete node;
	}

	StructType::operator std::string() {
		if (*name == "[anon]" && node)
			return node->typeStr();
		if (name->at(1) == '"')
			return "\e[32m%\e[33m" + name->substr(1) + "\e[0m";
		return "\e[32m" + *name + "\e[0m";
	}

	int StructType::width() const {
		int out = 0;
		if (!node) {
			// This is likely a named struct rather than a literal struct.
			std::string bare_name = name->at(0) == '%'? name->substr(1) : *name;
			if (bare_name.at(0) == '"')
				bare_name = bare_name.substr(1, bare_name.size() - 2);
			return knownStructs.at(bare_name)->width();
		}

		for (const Type *type: node->types)
			out += type->width();
		return out;
	}

	Type * StructType::extractType(const std::vector<int> &indices) const {
		// TODO!: Implement.
		node->debug();
		throw std::runtime_error("StructType::extractType is unimplemented.");
	}

	bool StructType::operator==(const Type &other) const {
		if (other.typeType() != TypeType::Struct)
			return false;
		node->debug();
		throw std::runtime_error("StructType::operator== is unimplemented.");
	}

	Type * getType(const ASTNode *node) {
		switch (node->symbol) {
			case FUNCTIONTYPE:  return new FunctionType(node);
			case TOK_INTTYPE:   return new IntType(atoi(node->lexerInfo->substr(1).c_str()));
			case TOK_FLOATTYPE: return new FloatType(FloatType::getType(*node->lexerInfo));
			case ARRAYTYPE:     return new  ArrayType(atoi(node->at(0)->lexerInfo->c_str()), getType(node->at(1)));
			case VECTORTYPE:    return new VectorType(atoi(node->at(0)->lexerInfo->c_str()), getType(node->at(1)));
			case POINTERTYPE:   return new PointerType(getType(node->at(0)));
			case TOK_VOID:      return new VoidType();
			case TOK_STRUCTVAR: return new StructType(node->lexerInfo, StructForm::Struct);
			case TOK_CLASSVAR:  return new StructType(node->lexerInfo, StructForm::Class);
			case TOK_UNIONVAR:  return new StructType(node->lexerInfo, StructForm::Union);
			case STRUCTDEF:     return new StructType(dynamic_cast<const StructNode *>(node));
			case TOK_GVAR:      return new GlobalTemporaryType(node);
			default: throw std::invalid_argument("Couldn't create Type from a node with symbol " +
			                                     std::string(Parser::getName(node->symbol)));
		}
	}

	std::ostream & operator<<(std::ostream &os, Type &type) {
		return os << std::string(type);
	}
}