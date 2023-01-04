#include "compiler/Variable.h"
#include "instruction/ModRInstruction.h"

namespace LL2W {
	std::string ModRInstruction::debugExtra() const {
		return operDebug("%");
	}

	std::string ModRInstruction::toString() const {
		return operString("%");
	}
	
	Instruction * ModRInstruction::copy() const {
		return new ModRInstruction(*this);
	}
}
