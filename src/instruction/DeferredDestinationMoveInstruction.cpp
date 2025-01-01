#include "compiler/Variable.h"
#include "instruction/DeferredDestinationMoveInstruction.h"

namespace LL2W {
	DeferredDestinationMoveInstruction::DeferredDestinationMoveInstruction(VariablePtr rs_, VariablePtr rd_,
	                                                                       int register_index):
			RType(std::move(rs_), nullptr, std::move(rd_), index_), registerIndex(register_index) {}

	std::string DeferredDestinationMoveInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd) + "\e[2m[\e[22m" + std::to_string(registerIndex)
			+ "\e[2m]\e[22m";
	}

	std::string DeferredDestinationMoveInstruction::toString() const {
		return rs->toString() + " -> " + rd->toString() + "[" + std::to_string(registerIndex) + "] (deferred; invalid)";
	}

	Instruction * DeferredDestinationMoveInstruction::copy() const {
		return new DeferredDestinationMoveInstruction(*this);
	}
}
