#include "compiler/Variable.h"
#include "instruction/AddIInstruction.h"

namespace LL2W {
	std::string AddIInstruction::debugExtra() const {
		return operDebug("+");
	}

	std::string AddIInstruction::toString() const {
		return operString("+");
	}
	
	Instruction * AddIInstruction::copy() const {
		return new AddIInstruction(*this);
	}
}
