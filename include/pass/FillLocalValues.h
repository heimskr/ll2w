#ifndef PASS_FILLLOCALVALUES_H_
#define PASS_FILLLOCALVALUES_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Sets the variable fields of all local values in all instructions. */
	void fillLocalValues(Function &);
}

#endif
