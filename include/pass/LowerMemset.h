#pragma once

#include <memory>

namespace LL2W {
	class Constant;
	class Function;
	class Instruction;
	class Variable;
}

namespace LL2W::Passes {
	/** Lowers llvm.memset.* intrinsics. */
	size_t lowerMemset(Function &);

	/** Sets up an argument for the Why memset instruction. If shouldLoad is true, the value at the address
	 *  represented by a global value will be loaded into the argument; otherwise, a global value's address itself will
	 *  be loaded into the argument. */
	void setupMemsetValue(Function &, const std::shared_ptr<Constant> &, std::shared_ptr<Instruction> &,
	                      std::shared_ptr<Variable> &, bool shouldLoad);
}
