#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Replaces alloca instructions with instructions that set the result variables to the assigned addresses.
	 *  Returns the number of alloca instructions that were replaced. Must not be called before variable assignment. */
	int lowerAlloca(Function &);
}
