#include "instruction/JumpSymbolInstruction.h"

namespace LL2W {
	std::string JumpSymbolInstruction::debugExtra() {
		return "\e[2m" + std::string(link? "::" : ":") + "\e[0m \e[91m&" + symbol + "\e[0m";
	}
}
