#include "compiler/Variable.h"
#include "instruction/LoadIndirectIInstruction.h"

namespace LL2W {
	LoadIndirectIInstruction::LoadIndirectIInstruction(Immediate imm, VariablePtr rd, WASMSize size):
		IType(nullptr, std::move(imm), std::move(rd)),
		HasSize(size) {}

	std::string LoadIndirectIInstruction::debugExtra() const {
		return "\e[2m[\e[22m" + colorize(imm, *rd) + "\e[2m] -> [\e[22m" + std::string(*rd) + "\e[2m]\e[22m" + sizeSuffix();
	}

	std::string LoadIndirectIInstruction::toString() const {
		return "[" + LL2W::toString(imm, *rd) + "] -> [" + rd->toString() + "]" + sizeSuffix();
	}

	Instruction * LoadIndirectIInstruction::copy() const {
		return new LoadIndirectIInstruction(*this);
	}
}
