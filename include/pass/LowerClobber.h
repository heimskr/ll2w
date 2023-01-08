#pragma once

#include <cstddef>

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Erases clobber/unclobber instructions if the targeted register isn't live-out or replaces them with push/pop
	 *  instructions if it is. */
	size_t lowerClobber(Function &);
}
