#include "compiler/Variable.h"
#include "instruction/JumpConditionalInstruction.h"

namespace LL2W {
	std::string JumpConditionalInstruction::debugExtra() {
		return "\e[2m" + std::string(link? "::" : ":") + "\e[0m " + std::to_string(addr) + " \e[2mif\e[22m " +
			std::string(*rs);
	}

	std::string JumpConditionalInstruction::toString() const {
		return std::string(link? "::" : ":") + " " + std::to_string(addr) + " if " + rs->toString();
	}
}
