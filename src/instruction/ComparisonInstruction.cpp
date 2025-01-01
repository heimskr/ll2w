#include "instruction/ComparisonInstruction.h"

namespace LL2W {
	bool ComparisonInstruction::isUnsigned() const {
		return cond == IcmpCond::Uge || cond == IcmpCond::Ugt || cond == IcmpCond::Ule || cond == IcmpCond::Ult;
	}
}
