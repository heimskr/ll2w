#include "compiler/Variable.h"
#include "instruction/IntIInstruction.h"

namespace LL2W {
	std::string IntIInstruction::debugExtra() const {
		return "\e[36m%int\e[39m " + colorize(imm);
	}

	std::string IntIInstruction::toString() const {
		return "%int " + LL2W::toString(imm);
	}
	
	Instruction * IntIInstruction::copy() const {
		return new IntIInstruction(*this);
	}
}
