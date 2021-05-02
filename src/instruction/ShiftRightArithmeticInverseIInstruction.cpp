#include "compiler/Variable.h"
#include "instruction/ShiftRightArithmeticInverseIInstruction.h"

namespace LL2W {
	std::string ShiftRightArithmeticInverseIInstruction::debugExtra() {
		return colorize(imm) + " \e[2m>>\e[0m " + std::string(*rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string ShiftRightArithmeticInverseIInstruction::toString() const {
		return LL2W::toString(imm) + " >> " + rs->toString() + " -> " + rd->toString();
	}
}
