#include "compiler/Variable.h"
#include "instruction/ShiftLeftLogicalIInstruction.h"

namespace LL2W {
	std::string ShiftLeftLogicalIInstruction::debugExtra() const {
#ifdef ENABLE_WHY_TYPES
		return std::string(*rs) + " \e[2m<<\e[22m " + colorize(imm) + "{ul} \e[2m->\e[22m " + std::string(*rd);
#else
		return std::string(*rs) + " \e[2m<<\e[22m " + colorize(imm) + " \e[2m->\e[22m " + std::string(*rd);
#endif
	}

	std::string ShiftLeftLogicalIInstruction::toString() const {
#ifdef ENABLE_WHY_TYPES
		return rs->toString() + " << " + LL2W::toString(imm, *rs) + "{ul} -> " + rd->toString();
#else
		return rs->toString() + " << " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
#endif
	}

	Instruction * ShiftLeftLogicalIInstruction::copy() const {
		return new ShiftLeftLogicalIInstruction(*this);
	}
}
