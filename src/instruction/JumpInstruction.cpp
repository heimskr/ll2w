#include "instruction/JumpInstruction.h"

namespace LL2W {
	std::string JumpInstruction::debugExtra() {
		return "\e[2m" + std::string(link? "::" : ":") + "\e[0m " + std::to_string(addr);
	}

	std::string JumpInstruction::toString() const {
		return std::string(link? "::" : ":") + " " + std::to_string(addr);
	}
}
