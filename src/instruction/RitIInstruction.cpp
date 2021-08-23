#include "compiler/Variable.h"
#include "instruction/RitIInstruction.h"

namespace LL2W {
	std::string RitIInstruction::debugExtra() {
		return "\e[36m%rit\e[39m " + colorize(imm);
	}

	std::string RitIInstruction::toString() const {
		return "%rit " + LL2W::toString(imm);
	}
}
