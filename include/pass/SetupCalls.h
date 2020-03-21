#ifndef PASS_SETUPCALLS_H_
#define PASS_SETUPCALLS_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Copies arguments into the argument registers or onto the stack as necessary before each call. */
	void setupCalls(Function &);
}

#endif
