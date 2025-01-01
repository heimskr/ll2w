#include "compiler/Variable.h"
#include "instruction/TypedPushInstruction.h"

namespace LL2W {
	TypedPushInstruction::TypedPushInstruction(VariablePtr rs_):
		RType(std::move(rs_), nullptr, nullptr) {}

	std::string TypedPushInstruction::debugExtra() const {
		return "\e[2m#[\e[22m " + std::string(*rs);
	}

	std::string TypedPushInstruction::toString() const {
		return "#[ " + rs->toString();
	}

	Instruction * TypedPushInstruction::copy() const {
		return new TypedPushInstruction(*this);
	}
}
