#pragma once

#include <set>
#include <string>

namespace LL2W {
	class ASTNode;

	struct LocalVariable {
		int id = -1;
		const std::string *name = nullptr;
		int arg = -1;   // decimal
		int scope = -1; // intnullbang
		int file = -1;  // intnullbang
		int line = -1;  // decimal
		int type = -1;  // intnullbang
		std::set<const std::string *> flags;

		LocalVariable(const ASTNode &node);
	};
}
