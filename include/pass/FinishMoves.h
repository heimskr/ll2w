#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Turns deferred source/destination moves into regular moves after register allocation. */
	void finishMoves(Function &);
}
