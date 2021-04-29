#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Splits up instructions that move from $r0 into register packs. */
	int splitResultMoves(Function &);
}
