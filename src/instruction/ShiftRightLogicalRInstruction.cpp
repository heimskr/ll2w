#include "compiler/Variable.h"
#include "instruction/ShiftRightLogicalRInstruction.h"

namespace LL2W {
	std::string ShiftRightLogicalRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m>>>\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string ShiftRightLogicalRInstruction::toString() const {
		return rs->toString() + " >>> " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * ShiftRightLogicalRInstruction::copy() const {
		return new ShiftRightLogicalRInstruction(*this);
	}
}
