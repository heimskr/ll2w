#include "instruction/DivuIInstruction.h"

namespace LL2W {
	std::string DivuIInstruction::debugExtra() const {
		return operDebug("/") + " /u";
	}

	std::string DivuIInstruction::toString() const {
		return operString("/") + " /u";
	}

	Instruction * DivuIInstruction::copy() const {
		return new DivuIInstruction(*this);
	}
}
