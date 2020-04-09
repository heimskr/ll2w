#ifndef PASS_LOWERSTACK_H_
#define PASS_LOWERSTACK_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers the StackStore and StackLoad intermediate instructions. */
	int lowerStack(Function &);
}

#endif
