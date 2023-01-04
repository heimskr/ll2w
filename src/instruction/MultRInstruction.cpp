#include "compiler/Variable.h"
#include "instruction/MultRInstruction.h"

namespace LL2W {
	MultRInstruction::MultRInstruction(VariablePtr rs_, VariablePtr rt_, int index_):
		LinkedST(std::move(rs_), std::move(rt_), nullptr, index_) {}

	std::string MultRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m*\e[22m " + std::string(*rt);
	}

	std::string MultRInstruction::toString() const {
		return rs->toString() + " * " + rt->toString();
	}
}
