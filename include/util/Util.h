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

	template <typename T>
	inline T updiv(T n, T d) {
		return n / d + (n % d? 1 : 0);
	}
}

#endif
