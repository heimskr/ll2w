#include "compiler/Variable.h"
#include "instruction/DivuiIInstruction.h"

namespace LL2W {
	std::string DivuiIInstruction::debugExtra() {
		return std::to_string(imm) + " \e[2m/\e[0m " + std::string(*rs) + " \e[2m->\e[0m " + std::string(*rd) + " /u";
	}

	std::string DivuiIInstruction::toString() const {
		return std::to_string(imm) + " / " + rs->toString() + " -> " + rd->toString() + " /u";
	}
}
