#ifndef ALLOCATOR_ALLOCATOR_H_
#define ALLOCATOR_ALLOCATOR_H_

#include <memory>

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
			enum class Result {Spilled, NotSpilled, Success};

			std::shared_ptr<Variable> lastSpill, lastSpillAttempt;

			Allocator(Function &function_): function(&function_) {}
			virtual ~Allocator() {}

			virtual Result attempt() = 0;
			int getAttempts() const { return attempts; }
	};
}

#endif
