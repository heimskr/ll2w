#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Inserts a prologue at the beginning of the function. */
	void insertPrologue(Function &);
}
