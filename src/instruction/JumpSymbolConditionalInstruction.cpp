#include "compiler/Variable.h"
#include "instruction/JumpSymbolConditionalInstruction.h"

namespace LL2W {
	std::string JumpSymbolConditionalInstruction::debugExtra() {
		return "\e[2m" + std::string(link? "::" : ":") + "\e[0m \e[91m&" + addr + " \e[39;2mif\e[22m " +
			std::string(*rs);
	}
}
