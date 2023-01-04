#include "compiler/Variable.h"
#include "instruction/AddRInstruction.h"

namespace LL2W {
	std::string AddRInstruction::debugExtra() {
		return operDebug("+");
	}

	std::string AddRInstruction::toString() const {
		return operString("+");
	}

	bool AddRInstruction::fixSignedness() {
		const bool out = rs->type->shareSignedness(rt->type);
		return rt->type->shareSignedness(rd->type) || out;
	}
	
	Instruction * AddRInstruction::copy() const {
		return new AddRInstruction(*this);
	}
}
