#include "compiler/Variable.h"
#include "instruction/OrRInstruction.h"

namespace LL2W {
	std::string OrRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m|\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string OrRInstruction::toString() const {
		return rs->toString() + " | " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * OrRInstruction::copy() const {
		return new OrRInstruction(*this);
	}
}
