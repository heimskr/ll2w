#include "compiler/Variable.h"
#include "instruction/SubIInstruction.h"

namespace LL2W {
	std::string SubIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m-\e[22m " + colorize(imm, *rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string SubIInstruction::toString() const {
		return rs->toString() + " - " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}
	
	Instruction * SubIInstruction::copy() const {
		return new SubIInstruction(*this);
	}
}
