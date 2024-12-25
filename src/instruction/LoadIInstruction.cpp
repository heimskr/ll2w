#include "compiler/Variable.h"
#include "instruction/LoadIInstruction.h"

namespace LL2W {
	LoadIInstruction::LoadIInstruction(Immediate imm, VariablePtr rd, WASMSize size):
		IType(nullptr, std::move(imm), std::move(rd)),
		HasSize(size) {}

	std::string LoadIInstruction::debugExtra() const {
		return "\e[2m[\e[22m" + colorize(imm, *rd, 1) + "\e[2m] ->\e[22m " + std::string(*rd) + sizeSuffix();
	}

	std::string LoadIInstruction::toString() const {
		return "[" + LL2W::toString(imm, *rd, 1) + "] -> " + rd->toString() + sizeSuffix();
	}

	Instruction * LoadIInstruction::copy() const {
		return new LoadIInstruction(*this);
	}
}
