#include "exception/TypeError.h"

namespace LL2W {
	TypeError::TypeError(const std::string &what_str, TypePtr type_):
		whatStr(what_str), type(type_? type_->copy() : nullptr) {}

	const char * TypeError::what() const throw() {
		return whatStr.c_str();
	}
}