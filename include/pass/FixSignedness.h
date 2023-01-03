#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Fixes missing signedness based on context. */
	void fixSignedness(Function &);
}
