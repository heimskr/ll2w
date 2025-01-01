#include "instruction/ModuIInstruction.h"

namespace LL2W {
	std::string ModuIInstruction::debugExtra() const {
		return operDebug("%") + " /u";
	}

	std::string ModuIInstruction::toString() const {
		return operString("%") + " /u";
	}

	Instruction * ModuIInstruction::copy() const {
		return new ModuIInstruction(*this);
	}
}
