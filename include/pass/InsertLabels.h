#ifndef PASS_INSERTLABELS_H_
#define PASS_INSERTLABELS_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Inserts label "instructions" at the beginning of every block in the function. */
	void insertLabels(Function &);
}

#endif
