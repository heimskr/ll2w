#ifndef PASS_LINEARSCAN_H_
#define PASS_LINEARSCAN_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Assigns registers using a linear scan algorithm. Returns the number of necessary spills. */
	int linearScan(Function &);
}

#endif
