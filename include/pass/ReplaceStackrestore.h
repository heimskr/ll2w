#ifndef PASS_REPLACESTACKRESTORE_H_
#define PASS_REPLACESTACKRESTORE_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Replaces calls to the llvm intrinsic llvm.stackrestore with instructions that restore the stack pointer from a
	 *  variable. */
	void replaceStackrestore(Function &);
}

#endif
