#pragma once

#include <cstddef>

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Transforms certain invalid Why instructions into valid ones. For example, because Load Halfword Immediate
	 *  doesn't exist, it has to be transformed into a Set instruction followed by a Load Halfword instruction. */
	size_t transformInstructions(Function &);
}
