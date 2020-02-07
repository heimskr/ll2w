#ifndef COMPILER_WHYINFO_H_
#define COMPILER_WHYINFO_H_

namespace LL2W {
	/** Contains constants pertaining to the Why.js architecture. */
	struct WhyInfo {
		static int wordSize; // in bytes
		static int savedCount, temporaryCount, assemblerCount;
		static int halfFloatWidth, floatWidth, doubleWidth, pointerWidth; // in bytes
	};
}

#endif
