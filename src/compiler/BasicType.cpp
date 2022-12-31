#include <iomanip>

#include "compiler/BasicType.h"
#include "parser/ASTNode.h"
#include "parser/Lexer.h"

namespace LL2W {
	BasicType::BasicType(const ASTNode &node):
		id(node.front()->atoi()),
		size(node.at(2)->atoi()),
		name(node.at(1)->lexerInfo),
		encoding(node.at(3)->lexerInfo) {}
}
