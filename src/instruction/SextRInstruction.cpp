#include "compiler/Variable.h"
#include "instruction/SextRInstruction.h"

namespace LL2W {
	SextRInstruction::SextRInstruction(VariablePtr rs_, VariablePtr rd_, int index_):
		RType(rs_, nullptr, rd_, index_) {}

	std::string SextRInstruction::debugExtra() {
		return "\e[1msext\e[22m " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string SextRInstruction::toString() const {
		return "sext " + rs->toString() + " -> " + rd->toString();
	}
}
