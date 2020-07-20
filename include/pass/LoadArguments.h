#ifndef PASS_LOADARGUMENTS_H_
#define PASS_LOADARGUMENTS_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Inserts instructions to load arguments from the stack as necessary. */
	void loadArguments(Function &);

	void loadArgumentsReadjust(Function &);
}

#endif
