#include "compiler/Variable.h"
#include "instruction/JumpRegisterInstruction.h"

namespace LL2W {
	std::string JumpRegisterInstruction::debugExtra() {
		return "\e[2m" + std::string(link? "::" : ":") + "\e[0m " + std::string(*rd);
	}

	std::string JumpRegisterInstruction::toString() const {
		return std::string(link? "::" : ":") + " " + rd->toString();
	}
}
