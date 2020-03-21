#ifndef PASS_REPLACEGETELEMENTPTRVALUES_H_
#define PASS_REPLACEGETELEMENTPTRVALUES_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Goes over all instructions and computes getelementptr values and places the results in a variable. */
	void replaceGetelementptrValues(Function &);
}

#endif
