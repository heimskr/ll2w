#ifndef EXCEPTION_TYPEERROR_H_
#define EXCEPTION_TYPEERROR_H_

#include <stdexcept>
#include "parser/Types.h"

namespace LL2W {
	class TypeError: public std::exception {
		private:
			std::string whatStr;

		public:
			TypePtr type;
			TypeError(const std::string &what_str, TypePtr type_ = nullptr);
			const char * what() const throw();
	};
}

#endif
