#include "StructNode.h"
#include "StringSet.h"

namespace LL2W {
	StructNode::StructNode(StructType type_, ASTNode *left, ASTNode *types_): ASTNode(STRUCTDEF, left->lexerInfo), type(type_) {
		name = StringSet::intern(left->extractName());
	}

	std::string StructNode::debugExtra() {
		return " " + *name;
	}
}