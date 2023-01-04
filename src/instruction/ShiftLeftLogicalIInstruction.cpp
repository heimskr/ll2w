#include "compiler/Variable.h"
#include "instruction/ShiftLeftLogicalIInstruction.h"

namespace LL2W {
	std::string ShiftLeftLogicalIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m<<\e[22m " + colorize(imm) + "{ul} \e[2m->\e[22m " + std::string(*rd);
	}

	std::string ShiftLeftLogicalIInstruction::toString() const {
		return rs->toString() + " << " + LL2W::toString(imm, *rs) + "{ul} -> " + rd->toString();
	}
	
	Instruction * ShiftLeftLogicalIInstruction::copy() const {
		return new ShiftLeftLogicalIInstruction(*this);
	}
}
