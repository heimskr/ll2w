#ifndef UTIL_UTIL_H_
#define UTIL_UTIL_H_

#include <string>

namespace LL2W {
	long parseLong(const std::string &);
	long parseLong(const std::string *);
	long parseLong(const char *);

	bool isNumeric(const std::string &);
	bool isNumeric(const std::string *);
	bool isNumeric(const char *);
}

#endif
