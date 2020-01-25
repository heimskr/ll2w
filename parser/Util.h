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

	/** Prints three strings if the middle isn't null. */
	void print(std::ostream &, const char *, const std::string *, const char * = "");
	/** Prints two strings and an int if the int isn't -1. */
	void print(std::ostream &, const char *, int, const char * = "");
}

#endif
