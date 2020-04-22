#ifndef PASS_TRIMBLOCKS_H_
#define PASS_TRIMBLOCKS_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Removes basic blocks that have no predecessors. This shouldn't cause any problems. */
	void trimBlocks(Function &);
}

#endif
