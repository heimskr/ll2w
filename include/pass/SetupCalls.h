#pragma once

#include <memory>

namespace LL2W {
	class Function;
	class Instruction;
	struct Constant;
}

namespace LL2W::Passes {
	/** Copies arguments into the argument registers or onto the stack as necessary before each call. */
	void setupCalls(Function &);

	/** Pushes a value to the stack before a call instruction. Returns how many bytes were pushed. */
	int pushCallValue(Function &, std::shared_ptr<Instruction>, std::shared_ptr<Constant>);

	/** Inserts a value into a precolored variable before a call instruction. */
	std::shared_ptr<Instruction>
	setupCallValue(Function &, std::shared_ptr<Variable>, std::shared_ptr<Instruction>, std::shared_ptr<Constant>);
}
