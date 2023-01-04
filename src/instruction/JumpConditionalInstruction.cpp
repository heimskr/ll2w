#include "compiler/Variable.h"
#include "instruction/JumpConditionalInstruction.h"

namespace LL2W {
	std::string JumpConditionalInstruction::debugExtra() const {
		return "\e[2m" + std::string(link? "::" : ":") + "\e[0m " + colorize(addr) + " \e[2mif\e[22m " +
			std::string(*rs);
	}

	std::string JumpConditionalInstruction::toString() const {
		return std::string(link? "::" : ":") + " " + LL2W::toString(addr) + " if " + rs->toString();
	}
	
	Instruction * JumpConditionalInstruction::copy() const {
		return new JumpConditionalInstruction(*this);
	}
}
