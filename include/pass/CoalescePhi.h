#ifndef PASS_COALESCEPHI_H_
#define PASS_COALESCEPHI_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Merges arguments of ϕ-instructions into single variables. */
	void coalescePhi(Function &);
}

#endif
