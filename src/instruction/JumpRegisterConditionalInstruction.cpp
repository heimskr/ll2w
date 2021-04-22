#include "compiler/Variable.h"
#include "instruction/JumpRegisterConditionalInstruction.h"

namespace LL2W {
	std::string JumpRegisterConditionalInstruction::debugExtra() {
		return "\e[2m" + std::string(link? "::" : ":") + "\e[0m " + std::string(*rd) + " \e[2mif\e[22m " +
			std::string(*rs);
	}

	std::string JumpRegisterConditionalInstruction::toString() const {
		return std::string(link? "::" : ":") + " " + rd->toString() + " if " + rs->toString();
	}
}
