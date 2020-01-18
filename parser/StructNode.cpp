#include <sstream>
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
	}

	StructNode::StructNode(StructShape shape_, ASTNode *types_): ASTNode(STRUCTDEF, "[anon]"), shape(shape_) {
		name = StringSet::intern("");
	}

	std::string StructNode::debugExtra() {
		std::stringstream out;
		if (shape == StructShape::Opaque) out << " opaque";
		else if (shape == StructShape::Packed) out << " packed";

		return out.str();
	}
}