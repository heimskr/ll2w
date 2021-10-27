#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Merges arguments of ϕ-instructions into single variables. If variablesOnly is true, the function simply aliases
	 *  the variables to each other and doesn't remove any instructions. */
	void coalescePhi(Function &, bool variablesOnly = false);

	/** This is an alternative to coalescePhi that translates ϕ-instructions by inserting move instructions in the
	 *  predecessor blocks. This breaks SSA form. */
	void movePhi(Function &);

	/** Produces and renders a graph of ϕ-instruction dependencies. Useful only for debugging. */
	void tracePhi(Function &);

	void cutPhi(Function &);
}
