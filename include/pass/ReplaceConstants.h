#ifndef PASS_REPLACECONSTANTS_H_
#define PASS_REPLACECONSTANTS_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Goes over all instructions and computes constant expressions and places the results in a variable. */
	void replaceConstants(Function &);
}

#endif
