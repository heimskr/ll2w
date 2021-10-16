#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Breaks up sets with a numeric immediate value larger than INT_MAX into a set and a lui. */
	void breakUpBigSets(Function &);
}
