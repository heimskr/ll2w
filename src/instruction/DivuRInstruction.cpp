#include "instruction/DivuRInstruction.h"

namespace LL2W {
	std::string DivuRInstruction::debugExtra() const {
		return operDebug("/") + " /u";
	}

	std::string DivuRInstruction::toString() const {
		return operString("/") + " /u";
	}

	Instruction * DivuRInstruction::copy() const {
		return new DivuRInstruction(*this);
	}
}
