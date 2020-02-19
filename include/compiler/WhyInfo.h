#ifndef COMPILER_WHYINFO_H_
#define COMPILER_WHYINFO_H_

#include <set>

namespace LL2W {
	/** Contains constants pertaining to the Why.js architecture. */
	struct WhyInfo {
		static int wordSize; // in bytes
		static int savedOffset, temporaryOffset, argumentOffset, returnValuesOffset, assemblerOffset;
		static int savedCount,  temporaryCount,  argumentCount,  returnValuesCount,  assemblerCount;
		static int generalPurposeRegisters;
		static int stackPointerOffset, framePointerOffset, returnAddressOffset;
		static int halfFloatWidth, floatWidth, doubleWidth, pointerWidth; // in bytes

		static std::set<int> makeRegisterPool();
	};
}

#endif
