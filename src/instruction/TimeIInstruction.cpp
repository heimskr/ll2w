#include "compiler/Variable.h"
#include "instruction/TimeIInstruction.h"

namespace LL2W {
	std::string TimeIInstruction::debugExtra() {
		return "\e[36m%time\e[39m " + colorize(imm);
	}

	std::string TimeIInstruction::toString() const {
		return "%time " + LL2W::toString(imm);
	}
}
