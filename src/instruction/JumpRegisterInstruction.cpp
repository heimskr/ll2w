#include "compiler/Variable.h"
#include "instruction/JumpRegisterInstruction.h"

namespace LL2W {
	std::string JumpRegisterInstruction::debugExtra() {
		return "\e[2m" + conditionPrefix() + std::string(link? "::" : ":") + "\e[0m " + std::string(*rd);
	}

	std::string JumpRegisterInstruction::toString() const {
		return conditionPrefix() + std::string(link? "::" : ":") + " " + rd->toString();
	}

	bool JumpRegisterInstruction::alwaysTerminal() const {
		return condition == Condition::None;
	}
}
