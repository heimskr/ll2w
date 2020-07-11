#ifndef PASS_COALESCEPHI_H_
#define PASS_COALESCEPHI_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Merges arguments of ϕ-instructions into single variables. If variablesOnly is true, the function simply aliases
	 *  the variables to each other and doesn't remove any instructions. */
	void coalescePhi(Function &, bool variablesOnly = false);
}

#endif
