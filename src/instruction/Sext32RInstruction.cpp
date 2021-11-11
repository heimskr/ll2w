#include "compiler/Variable.h"
#include "instruction/Sext32RInstruction.h"

namespace LL2W {
	Sext32RInstruction::Sext32RInstruction(VariablePtr rs_, VariablePtr rd_, int index_):
		RType(rs_, nullptr, rd_, index_) {}

	std::string Sext32RInstruction::debugExtra() {
		return "\e[1msext32\e[22m " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string Sext32RInstruction::toString() const {
		return "sext32 " + rs->toString() + " -> " + rd->toString();
	}
}
