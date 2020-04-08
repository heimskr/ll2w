#ifndef PASS_LOWERRET_H_
#define PASS_LOWERRET_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Replaces ret instructions with epilogues and corresponding Why instructions. */
	void lowerRet(Function &);
}

#endif
