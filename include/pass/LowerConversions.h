#ifndef PASS_LOWERCONVERSIONS_H_
#define PASS_LOWERCONVERSIONS_H_

#include <memory>

namespace LL2W {
	class Function;
	class Instruction;
	struct ConversionNode;
}

namespace LL2W::Passes {
	/** Lowers conversion instructions. */
	int lowerConversions(Function &);

	void lowerZext(Function &, std::shared_ptr<Instruction> &, ConversionNode *);
	void lowerTrunc(Function &, std::shared_ptr<Instruction> &, ConversionNode *);
}

#endif
