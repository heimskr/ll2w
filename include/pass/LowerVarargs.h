#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers the llvm.va_start and llvm.va_end intrinsics. */
	void lowerVarargsFirst(Function &);

	/** Copies the stack pointer into $m2 at the beginning of the function. */
	void lowerVarargsSecond(Function &);
}
