#include "instruction/ModuIInstruction.h"

namespace LL2W {
	std::string ModuIInstruction::debugExtra() {
		return operDebug("%") + " /u";
	}

	std::string ModuIInstruction::toString() const {
		return operString("%") + " /u";
	}
}
