#include "compiler/Variable.h"
#include "instruction/LoadIndirectIInstruction.h"

namespace LL2W {
	LoadIndirectIInstruction::LoadIndirectIInstruction(Immediate imm_, VariablePtr rd_, int index_):
		IType(nullptr, std::move(imm_), std::move(rd_), index_) {}

	std::string LoadIndirectIInstruction::debugExtra() const {
		return "\e[2m[\e[22m" + colorize(imm, *rd) + "\e[2m] -> [\e[22m" + std::string(*rd) + "\e[2m]\e[22m";
	}

	std::string LoadIndirectIInstruction::toString() const {
		return "[" + LL2W::toString(imm, *rd) + "] -> [" + rd->toString() + "]";
	}
	
	Instruction * LoadIndirectIInstruction::copy() const {
		return new LoadIndirectIInstruction(*this);
	}
}
