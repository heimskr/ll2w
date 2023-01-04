#include "compiler/Variable.h"
#include "instruction/ShiftLeftLogicalInverseIInstruction.h"

namespace LL2W {
	std::string ShiftLeftLogicalInverseIInstruction::debugExtra() {
		return colorize(imm, *rd) + " \e[2m<<\e[22m " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string ShiftLeftLogicalInverseIInstruction::toString() const {
		return LL2W::toString(imm, *rd) + " << " + rs->toString() + " -> " + rd->toString();
	}
	
	Instruction * ShiftLeftLogicalInverseIInstruction::copy() const {
		return new ShiftLeftLogicalInverseIInstruction(*this);
	}
}
