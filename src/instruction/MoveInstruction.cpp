#include "compiler/Variable.h"
#include "instruction/MoveInstruction.h"

namespace LL2W {
	MoveInstruction::MoveInstruction(VariablePtr rs_, VariablePtr rd_, int index_):
		LinkedSD(std::move(rs_), nullptr, std::move(rd_), index_) {}

	std::string MoveInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string MoveInstruction::toString() const {
		return rs->toString() + " -> " + rd->toString();
	}
	
	Instruction * MoveInstruction::copy() const {
		return new MoveInstruction(*this);
	}
}
