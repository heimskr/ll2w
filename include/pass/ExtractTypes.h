#pragma once

#include <cstddef>

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Attempts to find the type of every variable based on debug data and instruction types. */
	void extractTypes(Function &);
}
