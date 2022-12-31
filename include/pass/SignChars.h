#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Marks all chars (of any pointer level) of unknown signedness as unsigned. */
	void signChars(Function &);
}
