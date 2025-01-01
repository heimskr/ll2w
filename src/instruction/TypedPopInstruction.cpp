#include "compiler/Variable.h"
#include "instruction/TypedPopInstruction.h"

namespace LL2W {
	TypedPopInstruction::TypedPopInstruction(VariablePtr rd_):
		RType(nullptr, nullptr, std::move(rd_)) {}

	std::string TypedPopInstruction::debugExtra() const {
		return "\e[2m#]\e[22m " + std::string(*rd);
	}

	std::string TypedPopInstruction::toString() const {
		return "#] " + rd->toString();
	}

	Instruction * TypedPopInstruction::copy() const {
		return new TypedPopInstruction(*this);
	}
}
