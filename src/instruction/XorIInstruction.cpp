#include "compiler/Variable.h"
#include "instruction/XorIInstruction.h"

namespace LL2W {
	std::string XorIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2mx\e[0m " + colorize(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string XorIInstruction::toString() const {
		return rs->toString() + " x " + LL2W::toString(imm) + " -> " + rd->toString();
	}
}
