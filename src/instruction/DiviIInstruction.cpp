#include "compiler/Variable.h"
#include "instruction/DiviIInstruction.h"

namespace LL2W {
	std::string DiviIInstruction::debugExtra() const {
		return colorize(imm, *rs) + " \e[2m/\e[22m " + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string DiviIInstruction::toString() const {
		return LL2W::toString(imm, *rs) + " / " + rs->toString() + " -> " + rd->toString();
	}
	
	Instruction * DiviIInstruction::copy() const {
		return new DiviIInstruction(*this);
	}
}
