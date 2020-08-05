#ifndef ALLOCATOR_ALLOCATOR_H_
#define ALLOCATOR_ALLOCATOR_H_

#include <memory>
#include <string>

namespace LL2W {
	class Function;
	class Variable;

	class Allocator {
		protected:
			Function *function = nullptr;
			int spillCount = 0;
			int attempts = 0;
			bool argumentsPrecolored = false;

		public:
			enum class Result: int {Spilled = 1, NotSpilled = 2, Success = 3};

			std::shared_ptr<Variable> lastSpill, lastSpillAttempt;

			Allocator(Function &function_): function(&function_) {}
			virtual ~Allocator() {}

			virtual Result attempt() = 0;
			int getAttempts() const { return attempts; }

			static std::string stringify(Result result) {
				return result == Result::Spilled? "Spilled" : (result == Result::NotSpilled? "NotSpilled" :
					(result == Result::Success? "Success" : "?"));
			}
	};
}

#endif
