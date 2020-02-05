#ifndef COMPILER_VARIABLE_H_
#define COMPILER_VARIABLE_H_

#include <vector>

namespace LL2W {
	class Node;

	struct Variable {
		int id;
		std::list<Node *> uses;
		Node *definition;

		Variable(int id_, const std::list<Node *> &uses_ = {}, Node *definition_ = nullptr):
			id(id_), uses(uses_), definition(definition_) {}
	};
}

#endif
