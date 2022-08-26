#pragma once

#include <cstddef>

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers the select instruction. */
	size_t lowerSelect(Function &);
}
