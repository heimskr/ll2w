#pragma once

#include <memory>
#include <stdexcept>

namespace LL2W {
	class Type;

	using TypePtr = std::shared_ptr<Type>;

	class SignednessSharingError: public std::exception {
		private:
			const std::string whatStr;

		public:
			const TypePtr one;
			const TypePtr two;

			SignednessSharingError(std::string what_str, TypePtr one_, TypePtr two_);
			const char * what() const throw();
	};
}
