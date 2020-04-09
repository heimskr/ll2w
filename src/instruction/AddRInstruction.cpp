#include "compiler/Variable.h"
#include "instruction/AddRInstruction.h"

namespace LL2W {
	std::string AddRInstruction::debugExtra() {
		return operDebug("+");
	}

	std::string AddRInstruction::toString() const {
		return operString("+");
	}
}
