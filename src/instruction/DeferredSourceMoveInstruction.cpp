#include "compiler/Variable.h"
#include "instruction/DeferredSourceMoveInstruction.h"

namespace LL2W {
	DeferredSourceMoveInstruction::DeferredSourceMoveInstruction(VariablePtr rs, VariablePtr rd, int register_index):
		RType(std::move(rs), nullptr, std::move(rd)),
		registerIndex(register_index) {}

	std::string DeferredSourceMoveInstruction::debugExtra() const {
		return std::string(*rs) + "\e[2m[\e[22m" + std::to_string(registerIndex) + "\e[2m] ->\e[22m " + std::string(*rd);
	}

	std::string DeferredSourceMoveInstruction::toString() const {
		return rs->toString() + "[" + std::to_string(registerIndex) + "] -> " + rd->toString() + " (deferred; invalid)";
	}

	Instruction * DeferredSourceMoveInstruction::copy() const {
		return new DeferredSourceMoveInstruction(*this);
	}
}
