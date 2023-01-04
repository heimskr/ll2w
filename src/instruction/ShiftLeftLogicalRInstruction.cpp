#include "compiler/Variable.h"
#include "instruction/ShiftLeftLogicalRInstruction.h"

namespace LL2W {
	std::string ShiftLeftLogicalRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m<<\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string ShiftLeftLogicalRInstruction::toString() const {
		return rs->toString() + " << " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * ShiftLeftLogicalRInstruction::copy() const {
		return new ShiftLeftLogicalRInstruction(*this);
	}
}
