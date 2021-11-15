#pragma once

#include <cstddef>

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Splits up instructions that perform memory operations with register packs. */
	size_t splitLargeMemory(Function &);
}
