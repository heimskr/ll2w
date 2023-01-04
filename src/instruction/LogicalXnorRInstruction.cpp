#include "compiler/Variable.h"
#include "instruction/LogicalXnorRInstruction.h"

namespace LL2W {
	std::string LogicalXnorRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m!xx\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalXnorRInstruction::toString() const {
		return rs->toString() + " !xx " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * LogicalXnorRInstruction::copy() const {
		return new LogicalXnorRInstruction(*this);
	}
}
