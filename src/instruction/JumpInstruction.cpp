#include "instruction/JumpInstruction.h"

namespace LL2W {
	JumpInstruction::JumpInstruction(ValueType addr_, bool link_, Condition condition_, int index_):
		JType(nullptr, addr_, link_, index_), Conditional(condition_) {}

	std::string JumpInstruction::debugExtra() {
		return "\e[2m" + conditionPrefix() + (link? "::" : ":") + "\e[0m " + colorize(addr);
	}

	std::string JumpInstruction::toString() const {
		return conditionPrefix() + std::string(link? "::" : ":") + " " + LL2W::toString(addr);
	}

	bool JumpInstruction::isBlockTerminal() const {
		return condition == Condition::None;
	}
	
	Instruction * JumpInstruction::copy() const {
		return new JumpInstruction(*this);
	}
}
