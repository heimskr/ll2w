#include "compiler/Variable.h"
#include "instruction/StoreRInstruction.h"

namespace LL2W {
	StoreRInstruction::StoreRInstruction(VariablePtr rs_, VariablePtr rt_, int index_):
		LinkedST(std::move(rs_), std::move(rt_), nullptr, index_) {}

	std::string StoreRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m-> [\e[22;91m" + std::string(*rt) + "\e[39;2m]\e[22m";
	}

	std::string StoreRInstruction::toString() const {
		return rs->toString() + " -> [" + rt->toString() + "]";
	}
}
