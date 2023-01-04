#include "compiler/Variable.h"
#include "instruction/NorIInstruction.h"

namespace LL2W {
	std::string NorIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m~|\e[0m " + colorize(imm, *rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string NorIInstruction::toString() const {
		return rs->toString() + " ~| " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}
	
	Instruction * NorIInstruction::copy() const {
		return new NorIInstruction(*this);
	}
}
