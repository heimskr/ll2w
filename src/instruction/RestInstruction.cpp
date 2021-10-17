#include "compiler/Variable.h"
#include "instruction/RestInstruction.h"

namespace LL2W {
	RestInstruction::RestInstruction(int index_): RType(nullptr, nullptr, nullptr, index_) {}

	std::string RestInstruction::debugExtra() {
		return "<\e[36mrest\e[39m>";
	}

	std::string RestInstruction::toString() const {
		return "<rest>";
	}
}
