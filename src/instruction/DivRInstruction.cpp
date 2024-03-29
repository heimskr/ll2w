#include "compiler/Variable.h"
#include "instruction/DivRInstruction.h"

namespace LL2W {
	std::string DivRInstruction::debugExtra() const {
		return operDebug("/");
	}

	std::string DivRInstruction::toString() const {
		return operString("/");
	}
	
	Instruction * DivRInstruction::copy() const {
		return new DivRInstruction(*this);
	}
}
