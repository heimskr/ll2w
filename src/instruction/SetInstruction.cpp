#include "compiler/Variable.h"
#include "instruction/SetInstruction.h"

namespace LL2W {
	std::string SetInstruction::debugExtra() const {
		return "\e[91m" + colorize(imm, *rd, true) + " \e[2m->\e[22;32m " + std::string(*rd) + "\e[39m";
	}

	std::string SetInstruction::toString() const {
		return LL2W::toString(imm, true) + " -> " + rd->toString();
	}

	Instruction * SetInstruction::copy() const {
		return new SetInstruction(*this);
	}
}
