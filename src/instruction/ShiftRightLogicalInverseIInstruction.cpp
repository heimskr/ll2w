#include "compiler/Variable.h"
#include "instruction/ShiftRightLogicalInverseIInstruction.h"

namespace LL2W {
	std::string ShiftRightLogicalInverseIInstruction::debugExtra() const {
		return colorize(imm, *rd) + " \e[2m>>>\e[22m " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string ShiftRightLogicalInverseIInstruction::toString() const {
		return LL2W::toString(imm) + " >>> " + rs->toString() + " -> " + rd->toString();
	}

	Instruction * ShiftRightLogicalInverseIInstruction::copy() const {
		return new ShiftRightLogicalInverseIInstruction(*this);
	}
}
