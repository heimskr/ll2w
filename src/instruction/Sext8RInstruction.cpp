#include "compiler/Variable.h"
#include "instruction/Sext8RInstruction.h"

namespace LL2W {
	Sext8RInstruction::Sext8RInstruction(VariablePtr rs_, VariablePtr rd_, int index_):
		RType(rs_, nullptr, rd_, index_) {}

	std::string Sext8RInstruction::debugExtra() {
		return "\e[1msext8\e[22m " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string Sext8RInstruction::toString() const {
		return "sext8 " + rs->toString() + " -> " + rd->toString();
	}
}
