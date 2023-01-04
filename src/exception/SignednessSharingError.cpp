#include "exception/SignednessSharingError.h"

namespace LL2W {
	SignednessSharingError::SignednessSharingError(std::string what_str, TypePtr one_, TypePtr two_):
		whatStr(std::move(what_str)), one(std::move(one_)), two(std::move(two_)) {}

	const char * SignednessSharingError::what() const throw() {
		return whatStr.c_str();
	}
}
