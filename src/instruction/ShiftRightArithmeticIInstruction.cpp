#include "compiler/Variable.h"
#include "instruction/ShiftRightArithmeticIInstruction.h"

namespace LL2W {
	std::string ShiftRightArithmeticIInstruction::debugExtra() const {
#ifdef ENABLE_WHY_TYPES
		return std::string(*rs) + " \e[2m>>\e[22m " + colorize(imm) + "{ul} \e[2m->\e[22m " + std::string(*rd);
#else
		return std::string(*rs) + " \e[2m>>\e[22m " + colorize(imm) + " \e[2m->\e[22m " + std::string(*rd);
#endif
	}

	std::string ShiftRightArithmeticIInstruction::toString() const {
#ifdef ENABLE_WHY_TYPES
		return rs->toString() + " >> " + LL2W::toString(imm) + "{ul} -> " + rd->toString();
#else
		return rs->toString() + " >> " + LL2W::toString(imm) + " -> " + rd->toString();
#endif
	}

	Instruction * ShiftRightArithmeticIInstruction::copy() const {
		return new ShiftRightArithmeticIInstruction(*this);
	}
}
