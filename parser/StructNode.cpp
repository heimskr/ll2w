#include <sstream>
#include "StructNode.h"
#include "StringSet.h"

namespace LL2W {
	StructNode::StructNode(Shape shape_, ASTNode *left, ASTNode *types_):
	                      ASTNode(STRUCTDEF, left->lexerInfo), shape(shape_) {
		name = StringSet::intern(left->extractName());
	}

	std::string StructNode::debugExtra() {
		std::stringstream out;
		if (shape == Shape::Opaque) out << " opaque";
		else if (shape == Shape::Packed) out << " packed";

		return out.str();
	}
}