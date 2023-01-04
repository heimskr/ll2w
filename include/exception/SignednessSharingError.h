#pragma once

#include <memory>
#include <stdexcept>

namespace LL2W {
	struct IntType;

	using IntTypePtr = std::shared_ptr<IntType>;

	class SignednessSharingError: public std::exception {
		private:
			const std::string whatStr;

		public:
			const IntTypePtr one;
			const IntTypePtr two;

			SignednessSharingError(std::string what_str, IntTypePtr one_, IntTypePtr two_);
			const char * what() const throw();

			void printMore() const;
	};
}
