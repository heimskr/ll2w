#include "compiler/Variable.h"
#include "instruction/RitIInstruction.h"

namespace LL2W {
	RitIInstruction::RitIInstruction(Immediate imm_):
		IType(nullptr, std::move(imm_), nullptr) {}

	std::string RitIInstruction::debugExtra() const {
		return "\e[36m%rit\e[39m " + colorize(imm);
	}

	std::string RitIInstruction::toString() const {
		return "%rit " + LL2W::toString(imm);
	}

	Instruction * RitIInstruction::copy() const {
		return new RitIInstruction(*this);
	}
}
