#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Removes all LLVM instructions of the unreachable type. */
	size_t removeUnreachable(Function &);
}
