#include "compiler/Variable.h"
#include "instruction/ShiftRightArithmeticIInstruction.h"

namespace LL2W {
	std::string ShiftRightArithmeticIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m>>\e[22m " + colorize(imm) + "{ul} \e[2m->\e[22m " + std::string(*rd);
	}

	std::string ShiftRightArithmeticIInstruction::toString() const {
		return rs->toString() + " >> " + LL2W::toString(imm) + "{ul} -> " + rd->toString();
	}
}
