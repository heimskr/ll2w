#ifndef PASS_LOWERGETELEMENTPTR_H_
#define PASS_LOWERGETELEMENTPTR_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers getelementptr instructions. */
	int lowerGetelementptr(Function &);
}

#endif
