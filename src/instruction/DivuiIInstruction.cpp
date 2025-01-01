#include "compiler/Variable.h"
#include "instruction/DivuiIInstruction.h"

namespace LL2W {
	std::string DivuiIInstruction::debugExtra() const {
		return colorize(imm) + " \e[2m/\e[0m " + std::string(*rs) + " \e[2m->\e[0m " + std::string(*rd) + " /u";
	}

	std::string DivuiIInstruction::toString() const {
		return LL2W::toString(imm) + " / " + rs->toString() + " -> " + rd->toString() + " /u";
	}

	Instruction * DivuiIInstruction::copy() const {
		return new DivuiIInstruction(*this);
	}
}
