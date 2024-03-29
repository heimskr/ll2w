#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Inserts instructions to load arguments from the stack as necessary. */
	void loadArguments(Function &);

	/** Readjusts skips after the prologue is inserted. */
	void loadArgumentsReadjust(Function &);
}
