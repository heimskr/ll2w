#include "compiler/Variable.h"
#include "instruction/AndIInstruction.h"

namespace LL2W {
	std::string AndIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m&\e[0m " + colorize(imm, *rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string AndIInstruction::toString() const {
		return rs->toString() + " & " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}

	void AndIInstruction::fixSignedness() {
		rs->type->shareSignedness(rd->type);
	}
}
