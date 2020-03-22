#ifndef PASS_REPLACESTACKSAVE_H_
#define PASS_REPLACESTACKSAVE_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Replaces calls to the llvm intrinsic llvm.stacksave with instructions that save the stack pointer to a
	 *  variable. */
	void replaceStacksave(Function &);
}

#endif
