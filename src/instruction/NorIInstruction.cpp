#include "compiler/Variable.h"
#include "instruction/NorIInstruction.h"

namespace LL2W {
	std::string NorIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m~|\e[22m " + colorize(imm, *rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string NorIInstruction::toString() const {
		return rs->toString() + " ~| " + LL2W::toString(imm) + " -> " + rd->toString();
	}

	Instruction * NorIInstruction::copy() const {
		return new NorIInstruction(*this);
	}
}
