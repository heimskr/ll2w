#include "compiler/Variable.h"
#include "instruction/LogicalNorIInstruction.h"

namespace LL2W {
	std::string LogicalNorIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m!||\e[0m " + colorize(imm, *rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalNorIInstruction::toString() const {
		return rs->toString() + " !|| " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}
}
