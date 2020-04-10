#include "compiler/Variable.h"
#include "instruction/ShiftRightLogicalIInstruction.h"

namespace LL2W {
	std::string ShiftRightLogicalIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m>>>\e[0m " + std::to_string(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string ShiftRightLogicalIInstruction::toString() const {
		return rs->toString() + " >>> " + std::to_string(imm) + " -> " + rd->toString();
	}
}
