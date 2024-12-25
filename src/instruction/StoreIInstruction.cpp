#include "compiler/Variable.h"
#include "instruction/StoreIInstruction.h"

namespace LL2W {
	StoreIInstruction::StoreIInstruction(VariablePtr rs, Immediate imm, WASMSize size):
		IType(std::move(rs), std::move(imm), nullptr),
		HasSize(size) {}

	std::string StoreIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m-> [\e[22;91m" + colorize(imm, *rs, 1) + "\e[39;2m]\e[22m" + sizeSuffix();
	}

	std::string StoreIInstruction::toString() const {
		return rs->toString() + " -> [" + LL2W::toString(imm, *rs, 1) + "]" + sizeSuffix();
	}

	Instruction * StoreIInstruction::copy() const {
		return new StoreIInstruction(*this);
	}
}
