#include <iostream>
#include <sstream>

#include "parser/Lexer.h"
#include "parser/StructNode.h"
#include "parser/StringSet.h"
#include "parser/Parser.h"

namespace LL2W {
	StructNode::StructNode(std::initializer_list<TypePtr>  types, StructShape shape):
		ASTNode(llvmParser, LLVM_STRUCTDEF, ""),
		name(StringSet::intern("[anon]")),
		shape(shape),
		types(types) {}

	StructNode::StructNode(std::vector<TypePtr> types, StructShape shape):
		ASTNode(llvmParser, LLVM_STRUCTDEF, ""),
		name(StringSet::intern("[anon]")),
		shape(shape),
		types(std::move(types)) {}

	StructNode::StructNode(StructShape shape):
		ASTNode(llvmParser, LLVM_STRUCTDEF, ""),
		name(StringSet::intern("[anon]")),
		shape(shape),
		types{} {}

	StructNode::StructNode(StructShape shape, ASTNode *left, ASTNode *types):
		ASTNode(llvmParser, LLVM_STRUCTDEF, left->lexerInfo),
		name(StringSet::intern(left->extractName())),
		shape(shape) {
			if (left->symbol == LLVMTOK_CLASSVAR) {
				form = StructForm::Class;
			} else if (left->symbol == LLVMTOK_UNIONVAR) {
				form = StructForm::Union;
			}
			delete left;
			addTypes(types);
		}

	StructNode::StructNode(StructShape shape, ASTNode *types):
		ASTNode(llvmParser, LLVM_STRUCTDEF, "[anon]"),
		name(StringSet::intern("[anon]")),
		shape(shape) {
			addTypes(types);
		}

	void StructNode::addTypes(ASTNode *types_) {
		if (types_) {
			types.reserve(types_->size());
			for (const ASTNode *typenode: *types_)
				types.push_back(getType(typenode));
			delete types_;
		}
	}

	std::string StructNode::typeString() const {
		std::stringstream out;
		out << "\e[2m{\e[0m";
		auto begin = types.begin(), end = types.end();
		for (auto iter = begin; iter != end; ++iter) {
			if (iter != begin)
				out << "\e[2m, \e[0m";
			out << std::string(**iter);
		}
		out << "\e[2m}\e[0m";
		return out.str();
	}

	std::string StructNode::typeStringPlain() const {
		std::stringstream out;
		out << "{";
		auto begin = types.begin(), end = types.end();
		for (auto iter = begin; iter != end; ++iter) {
			if (iter != begin)
				out << ", ";
			out << (*iter)->toString();
		}
		out << "}";
		return out.str();
	}

	std::string StructNode::debugExtra() const {
		std::stringstream out;
		if (shape == StructShape::Opaque) {
			out << " opaque";
		} else {
			if (shape == StructShape::Packed)
				out << " packed";
			out << " " << typeString();
		}

		return out.str();
	}

	std::shared_ptr<StructNode> StructNode::copy() const {
		std::vector<TypePtr> type_copies;
		type_copies.reserve(types.size());
		for (TypePtr type: types)
			type_copies.push_back(type->copy());
		std::shared_ptr<StructNode> copied = std::make_shared<StructNode>(type_copies, shape);
		copied->form = form;
		copied->name = name;
		return copied;
	}
}