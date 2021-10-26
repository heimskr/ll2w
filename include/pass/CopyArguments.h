#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Copies the argument registers into temporaries at the beginning of a function. */
	void copyArguments(Function &);
}
