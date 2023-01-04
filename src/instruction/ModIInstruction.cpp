#include "instruction/ModIInstruction.h"

namespace LL2W {
	std::string ModIInstruction::debugExtra() {
		return operDebug("%");
	}

	std::string ModIInstruction::toString() const {
		return operString("%");
	}
	
	Instruction * ModIInstruction::copy() const {
		return new ModIInstruction(*this);
	}
}
