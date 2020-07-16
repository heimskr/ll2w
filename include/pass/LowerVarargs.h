#ifndef PASS_LOWERVARARGS_H_
#define PASS_LOWERVARARGS_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers the llvm.va_start and llvm.va_end intrinsics. */
	void lowerVarargs(Function &);
}

#endif
