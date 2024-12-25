#pragma once

#include <memory>

namespace LL2W {
	class Function;
	class Instruction;
	struct ConversionNode;
}

namespace LL2W::Passes {
	/** Lowers conversion instructions. */
	size_t lowerConversions(Function &);

	void lowerTrunc(Function &, const std::shared_ptr<Instruction> &, ConversionNode *);
	void lowerSext(Function &, const std::shared_ptr<Instruction> &, ConversionNode *);
}
