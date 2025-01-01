#include "compiler/Variable.h"
#include "instruction/StackPushInstruction.h"

namespace LL2W {
	StackPushInstruction::StackPushInstruction(VariablePtr rs_):
		RType(std::move(rs_), nullptr, nullptr) {}

	std::string StackPushInstruction::debugExtra() const {
		return "\e[2m[\e[22m " + std::string(*rs);
	}

	std::string StackPushInstruction::toString() const {
		return "[ " + rs->toString();
	}

	Instruction * StackPushInstruction::copy() const {
		return new StackPushInstruction(*this);
	}
}
