#pragma once

#include <cstddef>

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Discards the definitions of unused variables. */
	size_t discardUnusedVars(Function &);
}
