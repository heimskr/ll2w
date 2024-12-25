#include "compiler/Variable.h"
#include "instruction/LoadRInstruction.h"

namespace LL2W {
	LoadRInstruction::LoadRInstruction(VariablePtr rs, VariablePtr rd, WASMSize size):
		LinkedSD(std::move(rs), nullptr, std::move(rd)),
		HasSize(size) {}

	std::string LoadRInstruction::debugExtra() const {
		return "\e[2m[\e[0;91m" + std::string(*rs) + "\e[0;2m] ->\e[0m " + std::string(*rd) + sizeSuffix();
	}

	std::string LoadRInstruction::toString() const {
		return "[" + rs->toString() + "] -> " + rd->toString() + sizeSuffix();
	}

	Instruction * LoadRInstruction::copy() const {
		return new LoadRInstruction(*this);
	}
}
