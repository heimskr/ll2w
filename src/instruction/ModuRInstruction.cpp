#include "instruction/ModuRInstruction.h"

namespace LL2W {
	std::string ModuRInstruction::debugExtra() const {
		return operDebug("%") + " /u";
	}

	std::string ModuRInstruction::toString() const {
		return operString("%") + " /u";
	}

	Instruction * ModuRInstruction::copy() const {
		return new ModuRInstruction(*this);
	}
}
