#ifndef PARSER_UTIL_H_
#define PARSER_UTIL_H_

#include <ostream>
#include <unordered_set>

#include "Enums.h"

namespace LL2W {
	class ASTNode;

	void getFastmath(std::unordered_set<Fastmath> &, ASTNode *, bool destroy = true);

	void print(std::ostream &, const std::unordered_set<Fastmath> &, bool initial_space = true);
	std::ostream & operator<<(std::ostream &, const std::unordered_set<Fastmath> &);
}

#endif
