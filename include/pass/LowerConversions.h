#pragma once

#include <memory>

namespace LL2W {
	class Function;
	class Instruction;
	struct ConversionNode;
}

namespace LL2W::Passes {
	/** Lowers conversion instructions. */
	int lowerConversions(Function &);

	void lowerBasicConversion(Function &, std::shared_ptr<Instruction> &, ConversionNode *);
	void lowerTrunc(Function &, std::shared_ptr<Instruction> &, ConversionNode *);
	void lowerSext(Function &, std::shared_ptr<Instruction> &, ConversionNode *);
}
