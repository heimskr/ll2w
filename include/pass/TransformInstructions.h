#pragma once

#include <cstddef>

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Transforms certain invalid Why instructions into valid ones. */
	size_t transformInstructions(Function &);
}
