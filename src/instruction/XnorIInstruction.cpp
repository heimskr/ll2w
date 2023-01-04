#include "compiler/Variable.h"
#include "instruction/XnorIInstruction.h"

namespace LL2W {
	std::string XnorIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m~x\e[22m " + colorize(imm, *rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string XnorIInstruction::toString() const {
		return rs->toString() + " ~x " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}
	
	Instruction * XnorIInstruction::copy() const {
		return new XnorIInstruction(*this);
	}
}
