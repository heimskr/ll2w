#include "compiler/Variable.h"
#include "instruction/XnorRInstruction.h"

namespace LL2W {
	std::string XnorRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m~x\e[0m " + std::string(*rt) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string XnorRInstruction::toString() const {
		return rs->toString() + " ~x " + rt->toString() + " -> " + rd->toString();
	}
	
	Instruction * XnorRInstruction::copy() const {
		return new XnorRInstruction(*this);
	}
}
