#include "compiler/Variable.h"
#include "instruction/ShiftRightArithmeticIInstruction.h"

namespace LL2W {
	std::string ShiftRightArithmeticIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m>>\e[0m " + colorize(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string ShiftRightArithmeticIInstruction::toString() const {
		return rs->toString() + " >> " + LL2W::toString(imm) + " -> " + rd->toString();
	}
}
