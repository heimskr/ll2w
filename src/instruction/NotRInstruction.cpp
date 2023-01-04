#include "compiler/Variable.h"
#include "instruction/NotRInstruction.h"

namespace LL2W {
	NotRInstruction::NotRInstruction(VariablePtr rs_, VariablePtr rd_, int index_):
		LinkedSD(std::move(rs_), nullptr, std::move(rd_), index_) {}

	std::string NotRInstruction::debugExtra() const {
		return "\e[2m~\e[22m" + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string NotRInstruction::toString() const {
		return "~" + rs->toString() + " -> " + rd->toString();
	}
	
	Instruction * NotRInstruction::copy() const {
		return new NotRInstruction(*this);
	}
}
