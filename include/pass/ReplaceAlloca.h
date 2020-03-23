#ifndef PASS_REPLACEALLOCA_H_
#define PASS_REPLACEALLOCA_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Replaces alloca instructions with instructions that set the result variables to the assigned addresses. */
	void replaceAlloca(Function &);
}

#endif
