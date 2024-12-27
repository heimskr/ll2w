#pragma once

#include <memory>

namespace LL2W {
	class Function;
	class Instruction;
	struct BrCondNode;
	struct BrUncondNode;
}

namespace LL2W::Passes {
	/** Replaces LLVM branches with Why instructions. Returns the number of instructions replaced. */
	size_t lowerBranches(Function &);

	void lowerBranch(Function &, const std::shared_ptr<Instruction> &, BrCondNode *);
	void lowerBranch(Function &, const std::shared_ptr<Instruction> &, BrUncondNode *);
}
