#include "compiler/Variable.h"
#include "instruction/SetInstruction.h"

namespace LL2W {
	std::string SetInstruction::debugExtra() {
		return "\e[91m" + colorize(imm, *rd, true) + " \e[0;2m->\e[0;32m " + std::string(*rd) + "\e[0m";
	}

	std::string SetInstruction::toString() const {
		return LL2W::toString(imm, *rd, true) + " -> " + rd->toString();
	}
}
