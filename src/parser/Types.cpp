#include <iostream>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include "options.h"
#include "parser/ASTNode.h"
#include "parser/Lexer.h"
#include "parser/Parser.h"
#include "parser/Types.h"
#include "parser/StructNode.h"

namespace LL2W {
	bool Type::isInt() const {
		return typeType() == TypeType::Int;
	}

	IntType::operator std::string() {
		return "\e[33mi" + std::to_string(intWidth) + "\e[0m";
	}

	bool IntType::operator==(const Type &other) const {
		return this == &other ||
			(other.typeType() == TypeType::Int && dynamic_cast<const IntType &>(other).intWidth == intWidth);
	}

	ArrayType::operator std::string() {
		return "\e[2m[\e[0m" + std::to_string(count) + " \e[2mx\e[0m " + std::string(*subtype) + "\e[2m]\e[0m";
	}

	bool ArrayType::operator==(const Type &other) const {
		if (this == &other)
			return true;
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
		if (this == &other)
			return true;
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
		return this == &other ||
			(other.typeType() == TypeType::Float && dynamic_cast<const FloatType &>(other).type == type);
	}

	PointerType::operator std::string() {
		return std::string(*subtype) + "\e[1;2m*\e[0m";
	}

	bool PointerType::operator==(const Type &other) const {
		return this == &other ||
			(other.typeType() == TypeType::Pointer && *dynamic_cast<const PointerType &>(other).subtype == *subtype);
	}

	FunctionType::FunctionType(const ASTNode *node) {
		returnType = getType(node->at(0));
		if (node->children.size() == 3 || (1 < node->size() && node->at(1)->symbol == LLVM_TYPE_LIST)) {
			ASTNode *list = node->at(1);
			argumentTypes.reserve(list->children.size());
			for (ASTNode *child: *list)
				argumentTypes.push_back(getType(child));
		}

		ellipsis = node->size() == 3 || (1 < node->size() && node->at(1)->symbol == LLVMTOK_ELLIPSIS);
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

	TypePtr FunctionType::copy() const {
		std::vector<TypePtr> argument_types {};
		for (TypePtr argument_type: argumentTypes)
			argument_types.push_back(argument_type->copy());
		return std::make_shared<FunctionType>(returnType->copy(), argument_types);
	}

	bool FunctionType::operator==(const Type &other) const {
		if (this == &other)
			return true;
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

	StructType::StructType(std::shared_ptr<StructNode> node_):
		name(node_->name), form(node_->form), shape(node_->shape), node(node_) {}

	StructType::StructType(const StructNode *node_): StructType(std::shared_ptr<StructNode>(node_->copy())) {}

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
			return knownStructs.at(barename())->width();
		}

#ifndef STRUCT_PAD_X86
		for (const TypePtr &type: node->types)
			out += type->width();
#else
		int largest = 0;
		for (const TypePtr &type: node->types) {
			const int width = type->width();
			out += width + ((width - (out % width)) % width);
			if (largest < width)
				largest = width;
		}
		if (largest != 0)
			out += out % largest;
#endif
		return out;
	}

	TypePtr StructType::extractType(std::list<int> indices) const {
		// TODO!: Implement.
		node->debug();
		for (int index: indices) std::cout << index << " "; std::cout << "\n";
		TypePtr type = node->types.at(indices.front())->copy();
		if (indices.size() == 1) {
			std::cout << "[1] Returning " << std::string(*type) << "\n";
			return type;
		}

		std::shared_ptr<AggregateType> aggregate = std::dynamic_pointer_cast<AggregateType>(type);
		if (!aggregate)
			throw std::runtime_error("Expected an AggregateType in StructType::extractType");

		indices.pop_front();
		type = aggregate->extractType(indices);

		// while (!indices.empty()) {
		// 	AggregateType *aggregate = dynamic_cast<AggregateType *>(type);
		// 	if (!aggregate)
		// 		throw std::runtime_error("Expected an AggregateType in StructType::extractType");
		// 	indices.pop_front();
		// 	Type *new_type = aggregate->extractType(std::list<int> {indices.front()});
		// 	delete type;
		// 	type = new_type;
		// }

		std::cout << "Returning " << std::string(*type) << "\n";
		return type;
		// throw std::runtime_error("StructType::extractType is unimplemented.");
	}

	std::string StructType::barename() const {
		std::string out = name->at(0) == '%'? name->substr(1) : *name;
		return out.at(0) == '"'? out.substr(1, out.size() - 2) : out;
	}

	bool StructType::operator==(const Type &other) const {
		if (other.typeType() != TypeType::Struct)
			return false;
		node->debug();
		throw std::runtime_error("StructType::operator== is unimplemented.");
	}

	bool GlobalTemporaryType::operator==(const Type &other) const {
		return this == &other || (other.typeType() == TypeType::GlobalTemporary &&
		                          dynamic_cast<const GlobalTemporaryType &>(other).globalName == globalName);
	}

	TypePtr getType(const ASTNode *node) {
		switch (node->symbol) {
			case LLVM_FUNCTIONTYPE: return std::make_shared<FunctionType>(node);
			case LLVMTOK_INTTYPE:   return std::make_shared<IntType>(atoi(node->lexerInfo->substr(1).c_str()));
			case LLVMTOK_FLOATTYPE: return std::make_shared<FloatType>(FloatType::getType(*node->lexerInfo));
			case LLVM_POINTERTYPE:  return std::make_shared<PointerType>(getType(node->at(0)));
			case LLVMTOK_VOID:      return std::make_shared<VoidType>();
			case LLVMTOK_STRUCTVAR: return std::make_shared<StructType>(node->lexerInfo, StructForm::Struct);
			case LLVMTOK_CLASSVAR:  return std::make_shared<StructType>(node->lexerInfo, StructForm::Class);
			case LLVMTOK_UNIONVAR:  return std::make_shared<StructType>(node->lexerInfo, StructForm::Union);
			case LLVM_STRUCTDEF:    return std::make_shared<StructType>(dynamic_cast<const StructNode *>(node));
			case LLVMTOK_GVAR:      return std::make_shared<GlobalTemporaryType>(node);
			case LLVM_ARRAYTYPE:
				return std::make_shared<ArrayType>(atoi(node->at(0)->lexerInfo->c_str()),getType(node->at(1)));
			case LLVM_VECTORTYPE:
				return std::make_shared<VectorType>(atoi(node->at(0)->lexerInfo->c_str()),getType(node->at(1)));
			default: throw std::invalid_argument("Couldn't create Type from a node with symbol " +
			                                     std::string(llvmParser.getName(node->symbol)));
		}
	}

	std::ostream & operator<<(std::ostream &os, Type &type) {
		return os << std::string(type);
	}
}
