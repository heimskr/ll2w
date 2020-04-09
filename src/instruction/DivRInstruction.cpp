#include "compiler/Variable.h"
#include "instruction/DivRInstruction.h"

namespace LL2W {
	std::string DivRInstruction::debugExtra() {
		return operDebug("/");
	}

	std::string DivRInstruction::toString() const {
		return operString("/");
	}
}
