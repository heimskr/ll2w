#include "compiler/Variable.h"
#include "instruction/DivIInstruction.h"

namespace LL2W {
	std::string DivIInstruction::debugExtra() {
		return operDebug("/");
	}

	std::string DivIInstruction::toString() const {
		return operString("/");
	}
	
	Instruction * DivIInstruction::copy() const {
		return new DivIInstruction(*this);
	}
}
