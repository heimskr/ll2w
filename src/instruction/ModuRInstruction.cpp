#include "instruction/ModuRInstruction.h"

namespace LL2W {
	std::string ModuRInstruction::debugExtra() {
		return operDebug("%") + " /u";
	}

	std::string ModuRInstruction::toString() const {
		return operString("%") + " /u";
	}
}
