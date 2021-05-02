#include "compiler/Variable.h"
#include "instruction/ShiftRightLogicalInverseIInstruction.h"

namespace LL2W {
	std::string ShiftRightLogicalInverseIInstruction::debugExtra() {
		return colorize(imm) + " \e[2m>>>\e[0m " + std::string(*rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string ShiftRightLogicalInverseIInstruction::toString() const {
		return LL2W::toString(imm) + " >>> " + rs->toString() + " -> " + rd->toString();
	}
}
