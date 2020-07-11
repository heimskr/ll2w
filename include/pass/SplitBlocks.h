#ifndef PASS_SPLITBLOCKS_H_
#define PASS_SPLITBLOCKS_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Splits basic blocks such that no basic block contains more definitions than the number of physical registers.
	 *  Returns the number of times a block was split. */
	int splitBlocks(Function &);
}

#endif
