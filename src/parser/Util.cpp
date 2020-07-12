#include "parser/ASTNode.h"
#include "parser/Util.h"

namespace LL2W {
	void getFastmath(std::unordered_set<Fastmath> &flags, ASTNode *node, bool destroy) {
		for (ASTNode *child: *node) {
			for (const std::pair<const Fastmath, std::string> &pair: fastmath_map) {
				if (*child->lexerInfo == pair.second) {
					flags.insert(pair.first);
					break;
				}
			}
		}

		if (destroy)
			delete node;
	}

	void print(std::ostream &os, const std::unordered_set<Fastmath> &flags, bool initial_space) {
		for (auto begin = flags.cbegin(), iter = begin, end = flags.cend(); iter != end; ++iter) {
			if (initial_space || iter != begin)
				os << " ";
			os << "\e[34m" << fastmath_map.at(*iter) << "\e[39m";
		}
	}

	std::ostream & operator<<(std::ostream &os, const std::unordered_set<Fastmath> &flags) {
		print(os, flags);
		return os;
	}

	void print(std::ostream &os, const char *left, const std::string *middle, const char *right) {
		if (middle)
			os << left << *middle << right;
	}

	void print(std::ostream &os, const char *left, int n, const char *right) {
		if (n != -1)
			os << left << n << right;
	}
}