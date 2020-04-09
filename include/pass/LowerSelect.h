#ifndef PASS_LOWERSELECT_H_
#define PASS_LOWERSELECT_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers the select instruction. */
	int lowerSelect(Function &);
}

#endif
