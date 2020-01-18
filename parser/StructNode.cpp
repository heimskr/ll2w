#include <sstream>
#include "StructNode.h"
#include "StringSet.h"

namespace LL2W {
	StructNode::StructNode(StructType type_, ASTNode *left, ASTNode *types_): ASTNode(STRUCTDEF, left->lexerInfo), type(type_) {
		name = StringSet::intern(left->extractName());
	}

	std::string StructNode::debugExtra() {
		std::stringstream out;
		if (type == StructType::Opaque) out << " opaque";
		else if (type == StructType::Packed) out << " packed";

		return out.str();
	}
}