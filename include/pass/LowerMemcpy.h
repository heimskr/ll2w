#pragma once

#include <memory>

namespace LL2W {
	class Function;
	class Instruction;
	struct Value;
	class Variable;
}

namespace LL2W::Passes {
	/** Lowers llvm.memset.* intrinsics. */
	size_t lowerMemcpy(Function &);
}
