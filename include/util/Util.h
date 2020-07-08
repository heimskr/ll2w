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

	long roundUp(long, long);

	bool isNumeric(const std::string &);
	bool isNumeric(const std::string *);
	bool isNumeric(const char *);

	bool isHex(const char);

	std::string escape(const std::string &);

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

	/** Merges two sets. */
	template <typename S>
	S merge(const S &first, const S &second) {
		S out;
		for (const auto &item: first)
			out.insert(item);
		for (const auto &item: second)
			out.insert(item);
		return out;
	}

	/** Returns whether two sets have any items in common. */
	template <typename S>
	bool hasOverlap(const S &first, const S &second) {
		for (const auto &item: first) {
			if (second.count(item) != 0)
				return true;
		}
		return false;
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
