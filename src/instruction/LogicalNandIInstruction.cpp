#include "compiler/Variable.h"
#include "instruction/LogicalNandIInstruction.h"

namespace LL2W {
	std::string LogicalNandIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m!&&\e[0m " + colorize(imm, *rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalNandIInstruction::toString() const {
		return rs->toString() + " !&& " + LL2W::toString(imm) + " -> " + rd->toString();
	}

	Instruction * LogicalNandIInstruction::copy() const {
		return new LogicalNandIInstruction(*this);
	}
}
