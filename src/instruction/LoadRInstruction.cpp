#include "compiler/Variable.h"
#include "instruction/LoadRInstruction.h"

namespace LL2W {
	LoadRInstruction::LoadRInstruction(VariablePtr rs_, VariablePtr rd_, int index_):
		LinkedSD(std::move(rs_), nullptr, std::move(rd_), index_) {}

	std::string LoadRInstruction::debugExtra() {
		return "\e[2m[\e[0;91m" + std::string(*rs) + "\e[0;2m] ->\e[0m " + std::string(*rd);
	}

	std::string LoadRInstruction::toString() const {
		return "[" + rs->toString() + "] -> " + rd->toString();
	}
	
	Instruction * LoadRInstruction::copy() const {
		return new LoadRInstruction(*this);
	}
}
