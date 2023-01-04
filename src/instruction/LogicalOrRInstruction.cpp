#include "compiler/Variable.h"
#include "instruction/LogicalOrRInstruction.h"

namespace LL2W {
	std::string LogicalOrRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m||\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalOrRInstruction::toString() const {
		return rs->toString() + " || " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * LogicalOrRInstruction::copy() const {
		return new LogicalOrRInstruction(*this);
	}
}
