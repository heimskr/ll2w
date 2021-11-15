#pragma once

#include <cstddef>

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Splits up instructions that move from $r0 into register packs. */
	size_t splitResultMoves(Function &);
}
