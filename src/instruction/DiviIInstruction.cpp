#include "compiler/Variable.h"
#include "instruction/DiviIInstruction.h"

namespace LL2W {
	std::string DiviIInstruction::debugExtra() {
		return std::to_string(imm) + " \e[2m/\e[0m " + std::string(*rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string DiviIInstruction::toString() const {
		return std::to_string(imm) + " / " + rs->toString() + " -> " + rd->toString();
	}
}
