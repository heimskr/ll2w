#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Sometimes, spilling results in stores to one location immediately followed by a load from the same location.
	 *  This function replaces them with a register-to-register move. */
	void replaceStoresAndLoads(Function &);
}
