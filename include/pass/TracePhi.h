#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Produces and renders a graph of ϕ-instruction dependencies. Useful only for debugging. */
	void tracePhi(Function &);
}
