#ifndef PASS_LOWERBRANCHES_H_
#define PASS_LOWERBRANCHES_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Replaces LLVM branches with Why instructions. Returns the number of instructions replaced. */
	int lowerBranches(Function &);

	void lowerBranch(Function &, InstructionPtr &, BrCondNode *);
	void lowerBranch(Function &, InstructionPtr &, BrUncondNode *);
}

#endif
