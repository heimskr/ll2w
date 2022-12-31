#pragma once

#include <set>
#include <string>

namespace LL2W {
	class ASTNode;

	struct LocalVariable {
		int id = -1;
		const std::string *name = nullptr;
		int arg = -1;
		int scope = -1;
		int file = -1;
		int line = -1;
		int type = -1;
		std::set<const std::string *> flags;

		LocalVariable(const ASTNode &node);
	};
}
