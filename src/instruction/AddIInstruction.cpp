#include "compiler/Variable.h"
#include "instruction/AddIInstruction.h"

namespace LL2W {
	std::string AddIInstruction::debugExtra() {
		return operDebug("+");
	}

	std::string AddIInstruction::toString() const {
		return operString("+");
	}

	bool AddIInstruction::fixSignedness() {
		return rs->type->shareSignedness(rd->type);
	}
}
