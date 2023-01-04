#include "compiler/Variable.h"
#include "instruction/LogicalNorRInstruction.h"

namespace LL2W {
	std::string LogicalNorRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m!||\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalNorRInstruction::toString() const {
		return rs->toString() + " !|| " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * LogicalNorRInstruction::copy() const {
		return new LogicalNorRInstruction(*this);
	}
}
