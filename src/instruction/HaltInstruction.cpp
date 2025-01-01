#include "compiler/Variable.h"
#include "instruction/HaltInstruction.h"

namespace LL2W {
	HaltInstruction::HaltInstruction(int index_): RType(nullptr, nullptr, nullptr) {}

	std::string HaltInstruction::debugExtra() const {
		return "<\e[36mhalt\e[39m>";
	}

	std::string HaltInstruction::toString() const {
		return "<halt>";
	}

	Instruction * HaltInstruction::copy() const {
		return new HaltInstruction(*this);
	}
}
