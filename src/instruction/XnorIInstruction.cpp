#include "compiler/Variable.h"
#include "instruction/XnorIInstruction.h"

namespace LL2W {
	std::string XnorIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m~x\e[0m " + colorize(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string XnorIInstruction::toString() const {
		return rs->toString() + " ~x " + LL2W::toString(imm) + " -> " + rd->toString();
	}
}
