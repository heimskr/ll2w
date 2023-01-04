#include "compiler/Variable.h"
#include "instruction/LogicalNandRInstruction.h"

namespace LL2W {
	std::string LogicalNandRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m!&&\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalNandRInstruction::toString() const {
		return rs->toString() + " !&& " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * LogicalNandRInstruction::copy() const {
		return new LogicalNandRInstruction(*this);
	}
}
