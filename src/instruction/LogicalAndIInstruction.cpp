#include "compiler/Variable.h"
#include "instruction/LogicalAndIInstruction.h"

namespace LL2W {
	std::string LogicalAndIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m&&\e[0m " + colorize(imm, *rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalAndIInstruction::toString() const {
		return rs->toString() + " && " + LL2W::toString(imm) + " -> " + rd->toString();
	}

	Instruction * LogicalAndIInstruction::copy() const {
		return new LogicalAndIInstruction(*this);
	}
}
