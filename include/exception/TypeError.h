#pragma once

#include "parser/Types.h"

#include <stdexcept>

namespace LL2W {
	class TypeError: public std::exception {
		private:
			std::string whatStr;

		public:
			TypePtr type;
			TypeError(std::string what_str, TypePtr type_ = nullptr);
			const char * what() const throw();
	};
}
