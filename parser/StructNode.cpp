#include <sstream>

#include "Lexer.h"
#include "StructNode.h"
#include "StringSet.h"

namespace LL2W {
	StructNode::StructNode(StructShape shape_, ASTNode *left, ASTNode *types_):
	                      ASTNode(STRUCTDEF, left->lexerInfo), shape(shape_) {
		name = StringSet::intern(left->extractName());
		if (left->symbol == TOK_CLASSVAR)
			form = StructForm::Class;
		else if (left->symbol == TOK_UNIONVAR)
			form = StructForm::Union;
		delete left;
		addTypes(types_);
	}

	StructNode::StructNode(StructShape shape_, ASTNode *types_): ASTNode(STRUCTDEF, "[anon]"), shape(shape_) {
		name = StringSet::intern("");
		addTypes(types_);
	}

	StructNode::~StructNode() {
		for (Type *type: types)
			delete type;
	}

	void StructNode::addTypes(ASTNode *types_) {
		if (types_) {
			types.reserve(types_->size());
			for (const ASTNode *typenode: *types_)
				types.push_back(getType(typenode));
			delete types_;
		}
	}

	std::string StructNode::debugExtra() {
		std::stringstream out;
		if (shape == StructShape::Opaque) {
			out << " opaque";
		} else {
			if (shape == StructShape::Packed)
				out << " packed";
			out << " \e[2m{\e[0m";
			auto begin = types.begin(), end = types.end();
			for (auto iter = begin; iter != end; ++iter) {
				if (iter != begin)
					out << "\e[2m, \e[0m";
				out << std::string(**iter);
			}
			out << " \e[2m}\e[0m";
		}

		return out.str();
	}
}