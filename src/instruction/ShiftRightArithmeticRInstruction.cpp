#include "compiler/Variable.h"
#include "instruction/ShiftRightArithmeticRInstruction.h"

namespace LL2W {
	std::string ShiftRightArithmeticRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m>>\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string ShiftRightArithmeticRInstruction::toString() const {
		return rs->toString() + " >> " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * ShiftRightArithmeticRInstruction::copy() const {
		return new ShiftRightArithmeticRInstruction(*this);
	}
}
