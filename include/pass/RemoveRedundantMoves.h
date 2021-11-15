#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Removes move instructions that move a register to itself. */
	void removeRedundantMoves(Function &);
}
