#include <iomanip>

#include "compiler/BasicType.h"
#include "parser/ASTNode.h"
#include "parser/Lexer.h"

namespace LL2W {
	BasicType::BasicType(const ASTNode &node):
		LLVMType(node.at(1)->lexerInfo),
		id(node.front()->atoi()),
		size(node.at(2)->atoi()),
		encoding(node.at(3)->lexerInfo) {}

	bool BasicType::isSigned(Program *) {
		if (encoding != nullptr && encoding->find("_signed") != std::string::npos)
			return true;

		if (name != nullptr && name->find("unsigned") == std::string::npos && name->find("signed") != std::string::npos)
			return true;

		return false;
	}
}
