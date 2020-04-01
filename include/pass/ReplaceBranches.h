#ifndef PASS_REPLACEBRANCHES_H_
#define PASS_REPLACEBRANCHES_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Replaces LLVM branches with Why instructions. Returns the number of instructions replaced. */
	int replaceBranches(Function &);

	void replaceBranch(Function &, InstructionPtr &, BrCondNode *);
	void replaceBranch(Function &, InstructionPtr &, BrUncondNode *);
}

#endif
