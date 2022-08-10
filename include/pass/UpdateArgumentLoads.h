#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Updates the offsets in the adds inserted by loadArguments. This is necessary after spills and other allocations
	 *  have occurred because they move the stack pointer down. */
	void updateArgumentLoads(Function &, int offset);
}
