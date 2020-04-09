#ifndef PASS_LOWERSWITCH_H_
#define PASS_LOWERSWITCH_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Lowers the switch instruction. */
	int lowerSwitch(Function &);
}

#endif
