#include "compiler/Variable.h"
#include "instruction/StackPopInstruction.h"

namespace LL2W {
	StackPopInstruction::StackPopInstruction(VariablePtr rd_, int index_):
		RType(nullptr, nullptr, std::move(rd_), index_) {}

	std::string StackPopInstruction::debugExtra() const {
		return "\e[2m]\e[22m " + std::string(*rd);
	}

	std::string StackPopInstruction::toString() const {
		return "] " + rd->toString();
	}
	
	Instruction * StackPopInstruction::copy() const {
		return new StackPopInstruction(*this);
	}
}
