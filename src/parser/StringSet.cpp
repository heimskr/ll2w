#include "parser/StringSet.h"

#include <mutex>

namespace LL2W {
	std::unordered_set<std::string> StringSet::set;
	StringSet set;
	std::mutex stringsetMutex;

	StringSet::StringSet() {
		StringSet::set.max_load_factor(0.5);
	}

	const std::string * StringSet::intern(const char *str) {
		return intern(std::string(str));
	}

	const std::string * StringSet::intern(std::string str) {
		std::unique_lock lock(stringsetMutex);
		auto handle = set.insert(std::move(str));
		return &*handle.first;
	}

	const std::string * StringSet::unquote(const std::string *str) {
		if (2 <= str->size()) {
			if ((*str)[0] == '%') {
				if ((*str)[1] == '"' && str->back() == '"') {
					return intern('%' + str->substr(2, str->size() - 3));
				}
			} else if ((*str)[0] == '"' && str->back() == '"') {
				return intern(str->substr(1, str->size() - 2));
			}
		}
		return str;
	}
}
