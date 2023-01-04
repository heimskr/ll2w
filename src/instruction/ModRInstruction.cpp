#include "compiler/Variable.h"
#include "instruction/ModRInstruction.h"

namespace LL2W {
	std::string ModRInstruction::debugExtra() {
		return operDebug("%");
	}

	std::string ModRInstruction::toString() const {
		return operString("%");
	}
}
