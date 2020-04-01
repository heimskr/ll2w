#ifndef PASS_REPLACEICMP_H_
#define PASS_REPLACEICMP_H_

#include <memory>

namespace LL2W {
	class Function;
	struct IcmpNode;
	class Instruction;
}

namespace LL2W::Passes {
	/** Replaces icmp instructions with Why instructions. */
	int replaceIcmp(Function &);

	void replaceIcmp(Function &, std::shared_ptr<Instruction> &, IcmpNode *node);
}

#endif
