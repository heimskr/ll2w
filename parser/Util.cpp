#include "ASTNode.h"
#include "Util.h"

namespace LL2W {
	void getFastmath(std::unordered_set<Fastmath> &flags, ASTNode *node, bool destroy) {
		for (ASTNode *child: *node) {
			for (const std::pair<Fastmath, std::string> &pair: fastmath_map) {
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
			os << fastmath_map.at(*iter);
		}
	}

	std::ostream & operator<<(std::ostream &os, const std::unordered_set<Fastmath> &flags) {
		print(os, flags);
		return os;
	}
}