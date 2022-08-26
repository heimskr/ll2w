#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Replaces ret instructions with epilogues and corresponding Why instructions. */
	int lowerRet(Function &);
}
