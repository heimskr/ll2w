#include "compiler/Variable.h"
#include "instruction/SetptIInstruction.h"

namespace LL2W {
	std::string SetptIInstruction::debugExtra() {
		return "\e[36m%setpt\e[39m " + colorize(imm);
	}

	std::string SetptIInstruction::toString() const {
		return "%setpt " + LL2W::toString(imm);
	}
}
