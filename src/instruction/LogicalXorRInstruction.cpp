#include "compiler/Variable.h"
#include "instruction/LogicalXorRInstruction.h"

namespace LL2W {
	std::string LogicalXorRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2mxx\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalXorRInstruction::toString() const {
		return rs->toString() + " xx " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * LogicalXorRInstruction::copy() const {
		return new LogicalXorRInstruction(*this);
	}
}
