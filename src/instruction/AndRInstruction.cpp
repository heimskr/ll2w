#include "compiler/Variable.h"
#include "instruction/AndRInstruction.h"

namespace LL2W {
	std::string AndRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m&\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string AndRInstruction::toString() const {
		return rs->toString() + " & " + rt->toString() + " -> " + rd->toString();
	}

	bool AndRInstruction::fixSignedness() {
		bool out = rs->type->shareSignedness(rt->type);
		return rt->type->shareSignedness(rd->type) || out;
	}
	
	Instruction * AndRInstruction::copy() const {
		return new AndRInstruction(*this);
	}
}
