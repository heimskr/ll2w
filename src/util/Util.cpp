#include <cstdlib>
#include <stdexcept>

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

	long roundUp(long num, long to) {
		return num + ((to - (num % to)) % to);
	}

	bool isNumeric(const std::string &str) {
		for (char c: str) {
			if (c < '0' || '9' < c)
				return false;
		}
		return true;
	}

	bool isNumeric(const std::string *str) {
		return isNumeric(*str);
	}

	bool isNumeric(const char *str) {
		return isNumeric(std::string(str));
	}

	bool isHex(const char ch) {
		return ('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'f') || ('A' <= ch && ch <= 'F');
	}

	std::string escape(const std::string &str) {
		std::stringstream out;
		for (char ch: str) {
			if (ch == '"' || ch == '\\')
				out << '\\' << ch;
			else if (ch == '\t')
				out << "\\t";
			else if (ch == '\n')
				out << "\\n";
			else if (ch == '\r')
				out << "\\r";
			else
				out << ch;
		}
		return out.str();
	}
}
	