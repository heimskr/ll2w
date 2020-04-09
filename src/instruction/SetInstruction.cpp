#include "compiler/Variable.h"
#include "instruction/SetInstruction.h"

namespace LL2W {
	std::string SetInstruction::debugExtra() {
		return "\e[91m" + std::to_string(imm) + " \e[0;2m->\e[0;32m " + std::string(*rd) + "\e[0m";
	}

	std::string SetInstruction::toString() const {
		return std::to_string(imm) + " -> " + rd->toString();
	}
}