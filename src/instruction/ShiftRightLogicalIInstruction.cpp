#include "compiler/Variable.h"
#include "instruction/ShiftRightLogicalIInstruction.h"

namespace LL2W {
	std::string ShiftRightLogicalIInstruction::debugExtra() const {
#ifdef ENABLE_WHY_TYPES
		return std::string(*rs) + " \e[2m>>>\e[22m " + colorize(imm) + "{ul} \e[2m->\e[22m " + std::string(*rd);
#else
		return std::string(*rs) + " \e[2m>>>\e[22m " + colorize(imm) + " \e[2m->\e[22m " + std::string(*rd);
#endif
	}

	std::string ShiftRightLogicalIInstruction::toString() const {
#ifdef ENABLE_WHY_TYPES
		return rs->toString() + " >>> " + LL2W::toString(imm) + "{ul} -> " + rd->toString();
#else
		return rs->toString() + " >>> " + LL2W::toString(imm) + " -> " + rd->toString();
#endif
	}

	Instruction * ShiftRightLogicalIInstruction::copy() const {
		return new ShiftRightLogicalIInstruction(*this);
	}
}
