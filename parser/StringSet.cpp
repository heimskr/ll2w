#include "StringSet.h"

namespace LL2W {
	std::unordered_set<std::string> StringSet::set;
	StringSet set;

	StringSet::StringSet() {
		StringSet::set.max_load_factor(0.5);
	}

	const std::string * StringSet::intern(const char *str) {
		auto handle = set.insert(str);
		return &*handle.first;
	}
}
