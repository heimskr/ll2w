#include "compiler/Variable.h"
#include "instruction/ShiftRightLogicalIInstruction.h"

namespace LL2W {
	std::string ShiftRightLogicalIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m>>>\e[22m " + colorize(imm) + "{ul} \e[2m->\e[22m " + std::string(*rd);
	}

	std::string ShiftRightLogicalIInstruction::toString() const {
		return rs->toString() + " >>> " + LL2W::toString(imm) + "{ul} -> " + rd->toString();
	}
	
	Instruction * ShiftRightLogicalIInstruction::copy() const {
		return new ShiftRightLogicalIInstruction(*this);
	}
}
