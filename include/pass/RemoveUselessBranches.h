#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Removes all branch instructions that redundantly jump to the immediately following blocks. */
	void removeUselessBranches(Function &);
}
