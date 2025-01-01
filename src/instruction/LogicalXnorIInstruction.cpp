#include "compiler/Variable.h"
#include "instruction/LogicalXnorIInstruction.h"

namespace LL2W {
	std::string LogicalXnorIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m!xx\e[0m " + colorize(imm, *rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalXnorIInstruction::toString() const {
		return rs->toString() + " !xx " + LL2W::toString(imm) + " -> " + rd->toString();
	}

	Instruction * LogicalXnorIInstruction::copy() const {
		return new LogicalXnorIInstruction(*this);
	}
}
