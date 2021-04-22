#include "compiler/Variable.h"
#include "instruction/LuiInstruction.h"

namespace LL2W {
	std::string LuiInstruction::debugExtra() {
		return "lui: \e[91m" + colorize(imm) + " \e[0;2m->\e[0;32m " + std::string(*rd) + "\e[0m";
	}

	std::string LuiInstruction::toString() const {
		return "lui: " + LL2W::toString(imm) + " -> " + rd->toString();
	}
}
