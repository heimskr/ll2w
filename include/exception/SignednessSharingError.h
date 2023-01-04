#pragma once

#include <memory>
#include <stdexcept>

namespace LL2W {
	class Type;

	using TypeCPtr = std::shared_ptr<const Type>;

	class SignednessSharingError: public std::exception {
		private:
			const std::string whatStr;

		public:
			const TypeCPtr one;
			const TypeCPtr two;

			SignednessSharingError(std::string what_str, TypeCPtr one_, TypeCPtr two_);
			const char * what() const throw();
	};
}
