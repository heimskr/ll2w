#ifndef PASS_INSERTPROLOGUE_H_
#define PASS_INSERTPROLOGUE_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Inserts a prologue at the beginning of the function. */
	void insertPrologue(Function &);
}

#endif
