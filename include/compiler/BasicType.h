#pragma once

#include <string>

namespace LL2W {
	class ASTNode;

	struct BasicType {
		int id = -1;
		int size = -1; // decimal
		const std::string *name = nullptr;
		const std::string *encoding = nullptr;

		BasicType(const ASTNode &node);

		bool isSigned() const;
	};
}
