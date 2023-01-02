#include "compiler/Variable.h"
#include "instruction/TypedPushInstruction.h"

namespace LL2W {
	TypedPushInstruction::TypedPushInstruction(const VariablePtr &rs_, int index_):
		RType(rs_, nullptr, nullptr, index_) {}

	std::string TypedPushInstruction::debugExtra() {
		return "\e[2m#[\e[22m " + std::string(*rs);
	}

	std::string TypedPushInstruction::toString() const {
		return "#[ " + rs->toString();
	}
}
