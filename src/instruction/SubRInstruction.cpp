#include "compiler/Variable.h"
#include "instruction/SubRInstruction.h"

namespace LL2W {
	std::string SubRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m-\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string SubRInstruction::toString() const {
		return rs->toString() + " - " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * SubRInstruction::copy() const {
		return new SubRInstruction(*this);
	}
}
