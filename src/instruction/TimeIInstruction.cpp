#include "compiler/Variable.h"
#include "instruction/TimeIInstruction.h"

namespace LL2W {
	TimeIInstruction::TimeIInstruction(Immediate imm_, int index_):
		IType(nullptr, std::move(imm_), nullptr, index_) {}

	std::string TimeIInstruction::debugExtra() const {
		return "\e[36m%time\e[39m " + colorize(imm);
	}

	std::string TimeIInstruction::toString() const {
		return "%time " + LL2W::toString(imm);
	}
	
	Instruction * TimeIInstruction::copy() const {
		return new TimeIInstruction(*this);
	}
}
