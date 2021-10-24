#include "instruction/DivuRInstruction.h"

namespace LL2W {
	std::string DivuRInstruction::debugExtra() {
		return operDebug("/") + " /u";
	}

	std::string DivuRInstruction::toString() const {
		return operString("/") + " /u";
	}
}
