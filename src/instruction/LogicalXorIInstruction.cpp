#include "compiler/Variable.h"
#include "instruction/LogicalXorIInstruction.h"

namespace LL2W {
	std::string LogicalXorIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2mxx\e[0m " + colorize(imm) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalXorIInstruction::toString() const {
		return rs->toString() + " xx " + LL2W::toString(imm) + " -> " + rd->toString();
	}
}
