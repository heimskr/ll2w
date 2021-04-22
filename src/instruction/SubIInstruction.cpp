#include "compiler/Variable.h"
#include "instruction/SubIInstruction.h"

namespace LL2W {
	std::string SubIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m-\e[0m " + colorize(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string SubIInstruction::toString() const {
		return rs->toString() + " - " + LL2W::toString(imm) + " -> " + rd->toString();
	}
}
