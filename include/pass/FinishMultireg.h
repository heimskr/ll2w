#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Turns deferred source/destination moves into regular moves after register allocation and splits large loads
	 *  to/stores from register packs into a sequence of smaller loads/stores. */
	void finishMultireg(Function &);
}
