#include "compiler/Variable.h"
#include "instruction/TypedPopInstruction.h"

namespace LL2W {
	TypedPopInstruction::TypedPopInstruction(const VariablePtr &rd_, int index_):
		RType(nullptr, nullptr, rd_, index_) {}

	std::string TypedPopInstruction::debugExtra() {
		return "\e[2m#]\e[22m " + std::string(*rd);
	}

	std::string TypedPopInstruction::toString() const {
		return "#] " + rd->toString();
	}
}
