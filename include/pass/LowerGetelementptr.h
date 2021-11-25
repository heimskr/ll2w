#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers getelementptr instructions. */
	int lowerGetelementptr(Function &);
}
