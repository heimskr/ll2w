#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers calls to the llvm intrinsic llvm.stacksave to instructions that save the stack pointer to a variable. */
	void lowerStacksave(Function &);
}
