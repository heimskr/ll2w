#include "compiler/WhyInfo.h"

namespace LL2W {
	int WhyInfo::wordSize = 8;

	int WhyInfo::savedOffset = 62;
	int WhyInfo::savedCount  = 23;

	int WhyInfo::temporaryOffset = 39;
	int WhyInfo::temporaryCount  = 23;

	int WhyInfo::assemblerOffset = 102;
	int WhyInfo::assemblerCount  = 16;

	int WhyInfo::returnValuesOffset = 7;
	int WhyInfo::returnValuesCount  = 16;

	int WhyInfo::argumentOffset = 23;
	int WhyInfo::argumentCount  = 16;

	int WhyInfo::generalPurposeRegisters = WhyInfo::temporaryCount + WhyInfo::savedCount;

	int WhyInfo::stackPointerOffset  = 2;
	int WhyInfo::framePointerOffset  = 3;
	int WhyInfo::returnAddressOffset = 4;

	int WhyInfo::halfFloatWidth = 4;
	int WhyInfo::floatWidth = 8;
	int WhyInfo::doubleWidth = 8;
	int WhyInfo::pointerWidth = 8;

	std::set<int> WhyInfo::makeRegisterPool() {
		std::set<int> out;
		for (int i = temporaryOffset, max = temporaryOffset + temporaryCount; i < max; ++i)
			out.insert(i);
		for (int i = savedOffset, max = savedOffset + savedCount; i < max; ++i)
			out.insert(i);
		return out;
	}
}