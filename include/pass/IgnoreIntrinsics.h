#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Removes certain intrinsics, including @llvm.lifetime.*. */
	int ignoreIntrinsics(Function &);
}
