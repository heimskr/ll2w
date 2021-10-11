#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Adds an offset to $sp at the beginning of the function. This ends up being after the prologue, where the altered
	 *  registers are pushed and the stack pointer is moved to the frame pointer. */
	void insertStackSkip(Function &);

	/** After all spills have been recorded, change the immediate value in the previously inserted "$sp + 0 -> $sp"
	 *  instruction to the sum of the widths of all spills. */
	void readjustStackSkip(Function &);
}
