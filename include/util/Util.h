#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

#include <sstream>
#include <string>

namespace LL2W {
	long parseLong(const std::string &);
	long parseLong(const std::string *);
	long parseLong(const char *);

	bool isNumeric(const std::string &);
	bool isNumeric(const std::string *);
	bool isNumeric(const char *);

	template <typename T>
	std::string hex(T n) {
		std::stringstream ss;
		ss << std::hex << n;
		return ss.str();
	}
}

#endif
