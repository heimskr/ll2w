#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Replaces the @llvm.objectsize.* intrinsic with set instructions. */
	int lowerObjectsize(Function &);
}
