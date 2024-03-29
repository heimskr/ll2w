#include "compiler/Variable.h"
#include "instruction/LogicalNotRInstruction.h"

namespace LL2W {
	std::string LogicalNotRInstruction::debugExtra() const {
		if (rs == rd)
			return "\e[2m!\e[22m" + std::string(*rs) + "\e[2m.\e[22m";
		return "\e[2m!\e[22m" + std::string(*rs) + " \e[2m->\e[22m " + std::string(*rd);
	}

	std::string LogicalNotRInstruction::toString() const {
		if (rs == rd)
			return "!" + rs->toString() + ".";
		return "!" + rs->toString() + " -> " + rd->toString();
	}
	
	Instruction * LogicalNotRInstruction::copy() const {
		return new LogicalNotRInstruction(*this);
	}
}
