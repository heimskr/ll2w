#pragma once

#include <memory>

namespace LL2W {
	class Function;
	class Instruction;
	struct Value;
	class Variable;
}

namespace LL2W::Passes {
	/** Lowers llvm.memset.* intrinsics. */
	int lowerMemset(Function &);

	/** Sets up an argument for the WhyJS memset instruction. If shouldLoad is true, the value at the address
	 *  represented by a global value will be loaded into the argument; otherwise, a global value's address itself will
	 *  be loaded into the argument. */
	void setupMemsetValue(Function &, Value &, std::shared_ptr<Instruction> &, std::shared_ptr<Variable> &,
	                      bool shouldLoad, int assemblerIndex);
}
