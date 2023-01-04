#include "compiler/Variable.h"
#include "instruction/ShiftRightArithmeticInverseIInstruction.h"

namespace LL2W {
	std::string ShiftRightArithmeticInverseIInstruction::debugExtra() const {
		return colorize(imm, *rd) + " \e[2m>>\e[22m " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string ShiftRightArithmeticInverseIInstruction::toString() const {
		return LL2W::toString(imm, *rd) + " >> " + rs->toString() + " -> " + rd->toString();
	}
	
	Instruction * ShiftRightArithmeticInverseIInstruction::copy() const {
		return new ShiftRightArithmeticInverseIInstruction(*this);
	}
}
