#include "compiler/Variable.h"
#include "instruction/SetSymbolInstruction.h"

namespace LL2W {
	std::string SetSymbolInstruction::debugExtra() {
		return "\e[91m&" + imm + " \e[39;2m->\e[22;32m " + std::string(*rd) + "\e[39m";
	}
}
