#include <cstdlib>
#include <sstream>
#include <stdexcept>

#include "ASTNode.h"
#include "Lexer.h"
#include "Parser.h"
#include "Types.h"
#include "StructNode.h"

namespace LL2W {
	IntType::operator std::string() {
		return "\e[33mi" + std::to_string(width) + "\e[0m";
	}

	FloatType::operator std::string() {
		switch (type) {
			case FloatType::Type::Half: return "half";
			case FloatType::Type::Double: return "double";
			case FloatType::Type::FP128: return "fp128";
			case FloatType::Type::x86_FP80: return "x86_fp80";
			case FloatType::Type::PPC_FP128: return "ppc_fp128";
			default: throw std::runtime_error("Unrecognized float type: " + std::to_string(static_cast<int>(type)));
		}
	}

	FloatType::Type FloatType::getType(const std::string &str) {
		if (str == "half") return FloatType::Type::Half;
		else if (str == "double") return FloatType::Type::Double;
		else if (str == "fp128") return FloatType::Type::FP128;
		else if (str == "x86_fp80") return FloatType::Type::x86_FP80;
		else if (str == "ppc_fp128") return FloatType::Type::PPC_FP128;
		throw std::invalid_argument("Unknown float type: " + str);
	}

	FunctionType::FunctionType(const ASTNode *node) {
		returnType = getType(node->at(0));
		if (node->children.size() == 3) {
			ASTNode *list = node->at(2);
			argumentTypes.reserve(list->children.size());
			for (ASTNode *child: *list)
				argumentTypes.push_back(getType(child));
		}

		ellipse = node->at(1) != nullptr;
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

			if (ellipse)
				out << ", ...";
		} else if (ellipse) {
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

	StructType::StructType(const StructNode *node): name(node->name), form(node->form), shape(node->shape) {}

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
			default: throw std::invalid_argument("Couldn't create Type from a node with symbol " +
			                                     std::string(Parser::getName(node->symbol)));
		}
	}
}
