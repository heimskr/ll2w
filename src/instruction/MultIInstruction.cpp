#include "compiler/Variable.h"
#include "instruction/MultIInstruction.h"

namespace LL2W {
	std::string MultIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m*\e[0m " + std::to_string(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string MultIInstruction::toString() const {
		return rs->toString() + " * " + std::to_string(imm) + " -> " + rd->toString();
	}
}
