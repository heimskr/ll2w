#include "compiler/Variable.h"
#include "instruction/LoadIndirectIInstruction.h"

namespace LL2W {
	LoadIndirectIInstruction::LoadIndirectIInstruction(ValueType imm_, const std::shared_ptr<Variable> &rd_,
	int index_):
		IType(nullptr, imm_, rd_, index_) {}

	std::string LoadIndirectIInstruction::debugExtra() {
		return "\e[2m[\e[22m" + colorize(imm, *rs) + "\e[2m] -> [\e[22m" + std::string(*rd) + "\e[2m]\e[22m";
	}

	std::string LoadIndirectIInstruction::toString() const {
		return "[" + LL2W::toString(imm, *rs) + "] -> [" + rd->toString() + "]";
	}
}
