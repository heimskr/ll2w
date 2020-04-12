#ifndef PASS_REPLACEGETELEMENTPTRCONSTANTS_H_
#define PASS_REPLACEGETELEMENTPTRCONSTANTS_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Goes over all instructions and computes getelementptr constants and places the results in a variable. */
	void replaceGetelementptrConstants(Function &);
}

#endif
