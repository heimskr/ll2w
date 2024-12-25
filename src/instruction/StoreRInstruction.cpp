#include "compiler/Variable.h"
#include "instruction/StoreRInstruction.h"

namespace LL2W {
	StoreRInstruction::StoreRInstruction(VariablePtr rs, VariablePtr rt, WASMSize size):
		LinkedST(std::move(rs), std::move(rt), nullptr),
		HasSize(size) {}

	std::string StoreRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m-> [\e[22;91m" + std::string(*rt) + "\e[39;2m]\e[22m" + sizeSuffix();
	}

	std::string StoreRInstruction::toString() const {
		return rs->toString() + " -> [" + rt->toString() + "]" + sizeSuffix();
	}

	Instruction * StoreRInstruction::copy() const {
		return new StoreRInstruction(*this);
	}
}
