#include "compiler/Variable.h"
#include "instruction/LogicalAndRInstruction.h"

namespace LL2W {
	std::string LogicalAndRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m&&\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalAndRInstruction::toString() const {
		return rs->toString() + " && " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * LogicalAndRInstruction::copy() const {
		return new LogicalAndRInstruction(*this);
	}
}
