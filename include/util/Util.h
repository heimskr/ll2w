#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

#include <iostream>
#include <signal.h>
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

	inline std::ostream & warn() {
		return std::cerr << "\e[2m[\e[22;33m!\e[39;2m]\e[22;33m Warning: \e[39m";
	}

	inline std::ostream & error() {
		return std::cerr << "\e[2m[\e[22;31m!\e[39;2m]\e[22;31m Error: \e[39m";
	}

	inline std::ostream & info() {
		return std::cerr << "\e[2m[\e[22;36mi\e[39;2m]\e[22m ";
	}

	inline void debugger() {
		raise(SIGTRAP);
	}
}

#endif
