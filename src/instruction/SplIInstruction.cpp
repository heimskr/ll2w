#include "compiler/Variable.h"
#include "instruction/SplIInstruction.h"

namespace LL2W {
	SplIInstruction::SplIInstruction(Immediate imm, VariablePtr rd, WASMSize size):
		IType(nullptr, std::move(imm), std::move(rd)),
		HasSize(size) {}

	std::string SplIInstruction::debugExtra() const {
		return "\e[2m[\e[22;92m$fp\e[39;2m - \e[22m" + colorize(imm, *rd, 1) + "\e[2m] ->\e[22m " + std::string(*rd) + sizeSuffix();
	}

	std::string SplIInstruction::toString() const {
		return "[$fp - " + LL2W::toString(imm, false) + "] -> " + rd->toString() + sizeSuffix();
	}

	Instruction * SplIInstruction::copy() const {
		return new SplIInstruction(*this);
	}
}
