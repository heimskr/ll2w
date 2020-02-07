#include "compiler/WhyInfo.h"

namespace LL2W {
	int WhyInfo::wordSize = 8;

	int WhyInfo::savedCount = 23;
	int WhyInfo::temporaryCount = 23;
	int WhyInfo::assemblerCount = 16;

	int WhyInfo::halfFloatWidth = 4;
	int WhyInfo::floatWidth = 8;
	int WhyInfo::doubleWidth = 8;
	int WhyInfo::pointerWidth = 8;
}