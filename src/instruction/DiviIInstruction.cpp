#include "compiler/Variable.h"
#include "instruction/DiviIInstruction.h"

namespace LL2W {
	std::string DiviIInstruction::debugExtra() {
		return colorize(imm) + " \e[2m/\e[0m " + std::string(*rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string DiviIInstruction::toString() const {
		return LL2W::toString(imm) + " / " + rs->toString() + " -> " + rd->toString();
	}
}
