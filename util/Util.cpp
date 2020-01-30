#include <cstdlib>

#include "util/Util.h"

namespace LL2W {
	long parseLong(const std::string &str) {
		const char *c_str = str.c_str();
		char *end;
		long parsed = strtol(c_str, &end, 10);
		if (c_str + str.length() != end)
			throw std::invalid_argument("Not an integer: \"" + str + "\"");
		return parsed;
	}

	long parseLong(const std::string *str) {
		return parseLong(*str);
	}

	long parseLong(const char *str) {
		return parseLong(std::string(str));
	}
}
	