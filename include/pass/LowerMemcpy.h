#pragma once

#include <cstddef>

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers llvm.memcpy.* intrinsics. */
	size_t lowerMemcpy(Function &);
}
