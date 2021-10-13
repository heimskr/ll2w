#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers the freeze instruction by replacing it with a move. */
	size_t lowerFreeze(Function &);
}
