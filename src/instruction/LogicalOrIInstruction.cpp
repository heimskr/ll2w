#include "compiler/Variable.h"
#include "instruction/LogicalOrIInstruction.h"

namespace LL2W {
	std::string LogicalOrIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m||\e[0m " + colorize(imm, *rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalOrIInstruction::toString() const {
		return rs->toString() + " || " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}
}
