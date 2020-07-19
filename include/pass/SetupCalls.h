#ifndef PASS_SETUPCALLS_H_
#define PASS_SETUPCALLS_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Copies arguments into the argument registers or onto the stack as necessary before each call. */
	void setupCalls(Function &);

	/** Pushes a value to the stack before a call instruction. */
	void pushCallValue(Function &, std::shared_ptr<Instruction>, std::shared_ptr<Constant>, bool sized);

	/** Inserts a value into a precolored variable before a call instruction. */
	void setupCallValue(Function &, std::shared_ptr<Variable>, std::shared_ptr<Instruction>, std::shared_ptr<Constant>);
}

#endif
