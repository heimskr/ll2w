#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <set>

namespace LL2W {
	class Node;

	struct Variable {
		int id;
		std::set<BasicBlock *> uses;
		BasicBlock *definition;

		Variable(int id_, BasicBlock *definition_ = nullptr, const std::set<BasicBlock *> &uses_ = {}):
			id(id_), uses(uses_), definition(definition_) {}
	};
}

#endif
