#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <vector>

namespace LL2W {
	class Node;

	struct Variable {
		int id;
		std::unordered_set<BasicBlock *> uses;
		BasicBlock *definition;

		Variable(int id_, BasicBlock *definition_ = nullptr, const std::unordered_set<BasicBlock *> &uses_ = {}):
			id(id_), uses(uses_), definition(definition_) {}
	};
}

#endif
