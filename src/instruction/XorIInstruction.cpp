#include "compiler/Variable.h"
#include "instruction/XorIInstruction.h"

namespace LL2W {
	std::string XorIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2mx\e[22m " + colorize(imm, *rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string XorIInstruction::toString() const {
		return rs->toString() + " x " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}
}
