#include "compiler/Variable.h"
#include "instruction/XorRInstruction.h"

namespace LL2W {
	std::string XorRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2mx\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string XorRInstruction::toString() const {
		return rs->toString() + " x " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * XorRInstruction::copy() const {
		return new XorRInstruction(*this);
	}
}
