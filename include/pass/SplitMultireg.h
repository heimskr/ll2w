#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Splits up instructions that operate on variables that have been assigned multiple physical registers. */
	int splitMultireg(Function &);
}
