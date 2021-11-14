#include "compiler/Variable.h"
#include "instruction/Sext16RInstruction.h"

namespace LL2W {
	Sext16RInstruction::Sext16RInstruction(VariablePtr rs_, VariablePtr rd_, int index_):
		RType(rs_, nullptr, rd_, index_) {}

	std::string Sext16RInstruction::debugExtra() {
		return "\e[1msext16\e[22m " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string Sext16RInstruction::toString() const {
		return "sext16 " + rs->toString() + " -> " + rd->toString();
	}
}
