#include "compiler/Variable.h"
#include "instruction/LoadIInstruction.h"

namespace LL2W {
	LoadIInstruction::LoadIInstruction(Immediate imm_, VariablePtr rd_, int index_):
		IType(nullptr, std::move(imm_), std::move(rd_), index_) {}

	std::string LoadIInstruction::debugExtra() const {
		return "\e[2m[\e[22m" + colorize(imm, *rd, 1) + "\e[2m] ->\e[22m " + std::string(*rd);
	}

	std::string LoadIInstruction::toString() const {
		return "[" + LL2W::toString(imm, *rd, 1) + "] -> " + rd->toString();
	}
	
	Instruction * LoadIInstruction::copy() const {
		return new LoadIInstruction(*this);
	}
}
