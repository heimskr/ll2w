#include "compiler/Variable.h"
#include "instruction/MultRInstruction.h"

namespace LL2W {
	MultRInstruction::MultRInstruction(VariablePtr rs_, VariablePtr rt_, int index_):
		RType(rs_, rt_, nullptr, index_) {}

	std::string MultRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m*\e[0m " + std::string(*rt);
	}

	std::string MultRInstruction::toString() const {
		return rs->toString() + " * " + rt->toString();
	}
}
