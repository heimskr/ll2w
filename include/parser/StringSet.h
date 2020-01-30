#ifndef PARSER_STRINGSET_H_
#define PARSER_STRINGSET_H_

#include <string>
#include <unordered_set>

namespace LL2W {
	struct StringSet {
		StringSet();

		static std::unordered_set<std::string> set;
		static const std::string * intern(const char *);
		static const std::string * intern(const std::string &);
	};
}

#endif
