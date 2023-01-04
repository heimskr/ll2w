#include "exception/SignednessSharingError.h"
#include "parser/Types.h"
#include "util/Util.h"

namespace LL2W {
	SignednessSharingError::SignednessSharingError(std::string what_str, IntTypePtr one_, IntTypePtr two_):
		whatStr(std::move(what_str)), one(std::move(one_)), two(std::move(two_)) {}

	const char * SignednessSharingError::what() const throw() {
		return whatStr.c_str();
	}

	void SignednessSharingError::printMore() const {
		info() << "This (" << *one << "):\n\e[2m" << Util::translateBacktrace(one->getSignednessBacktrace());
		info() << "\e[22mOther (" << *two << "):\n\e[2m"
				<< Util::translateBacktrace(two->getSignednessBacktrace()) << "\e[22m";
		// info() << "Current backtrace:\n\e[2m" << Util::translateBacktrace(Util::getBacktrace())
		// 		<< "\e[22m";
	}
}
