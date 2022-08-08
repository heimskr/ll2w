#pragma once

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

	template <typename Cont>
	bool equalTypes(const Cont &one, const Cont &two) {
		if (one.size() != two.size())
			return false;
		for (size_t i = 0, size = one.size(); i < size; ++size) {
			if (*one[i] != *two[i])
				return false;
		}
		return true;
	}
}
