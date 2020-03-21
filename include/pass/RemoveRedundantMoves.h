#ifndef PASS_REMOVEREDUNDANTMOVES_H_
#define PASS_REMOVEREDUNDANTMOVES_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Removes move instructions that move a register to itself. */
	void removeRedundantMoves(Function &);
}

#endif
