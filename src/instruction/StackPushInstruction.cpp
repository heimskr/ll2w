#include "compiler/Variable.h"
#include "instruction/StackPushInstruction.h"

namespace LL2W {
	StackPushInstruction::StackPushInstruction(const VariablePtr &rs_, int index_):
		RType(rs_, nullptr, nullptr, index_) {}

	std::string StackPushInstruction::debugExtra() {
		return "\e[2m[\e[22m " + std::string(*rs);
	}

	std::string StackPushInstruction::toString() const {
		return "[ " + rs->toString();
	}
}
