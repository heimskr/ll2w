#include <iomanip>

#include "compiler/BasicType.h"
#include "parser/ASTNode.h"
#include "parser/Lexer.h"

namespace LL2W {
	BasicType::BasicType(const ASTNode &node):
		LLVMType(node.front()->atoi(), node.at(1)->lexerInfo),
		size(node.at(2)->atoi()),
		encoding(node.at(3)->lexerInfo) {}

	Signedness BasicType::getSignedness(Program *) {
		if (encoding != nullptr && encoding->find("_signed") != std::string::npos)
			return Signedness::Signed;

		if (name != nullptr && name->find("unsigned") != std::string::npos)
			return Signedness::Unsigned;

		if (name != nullptr && name->find("signed") != std::string::npos)
			return Signedness::Signed;

		return Signedness::Unknown;
	}

	BasicType::operator std::string() {
		return '!' + std::to_string(id) + " = !DIBasicType(name: " + (name == nullptr? "null" : *name) + ", size: " +
			std::to_string(size) + ", encoding: " + (encoding == nullptr? "null" : *encoding) + ")";
	}
}
