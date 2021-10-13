#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers the switch instruction. */
	int lowerSwitch(Function &);
}
