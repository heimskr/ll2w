#include "compiler/Variable.h"
#include "instruction/LogicalXorIInstruction.h"

namespace LL2W {
	std::string LogicalXorIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2mxx\e[0m " + colorize(imm, *rs) + " \e[2m->\e[0m " + std::string(*rd);
	}

	std::string LogicalXorIInstruction::toString() const {
		return rs->toString() + " xx " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}
	
	Instruction * LogicalXorIInstruction::copy() const {
		return new LogicalXorIInstruction(*this);
	}
}
