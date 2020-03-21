#ifndef PASS_MERGEALLBLOCKS_H_
#define PASS_MERGEALLBLOCKS_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Merges each terminal-free basic block with the basic block following it. */
	void mergeAllBlocks(Function &);
}

#endif
