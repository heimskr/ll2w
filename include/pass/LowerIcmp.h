#pragma once

#include <memory>

namespace LL2W {
	class Function;
	struct IcmpNode;
	class Instruction;
}

namespace LL2W::Passes {
	/** Lowers icmp instructions with Why instructions. */
	int lowerIcmp(Function &);

	void lowerIcmp(Function &, std::shared_ptr<Instruction> &, IcmpNode *node);
}
