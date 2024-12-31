#include "compiler/Variable.h"
#include "instruction/SpsIInstruction.h"

namespace LL2W {
	SpsIInstruction::SpsIInstruction(Immediate imm, VariablePtr rs):
		IType(std::move(rs), std::move(imm), nullptr) {}

	std::string SpsIInstruction::debugExtra() const {
		return std::string(*rs) + "\e[2m -> [\e[22;92m$fp\e[39;2m - \e[22m" + colorize(imm, false) + "\e[2m]\e[22m";
	}

	std::string SpsIInstruction::toString() const {
		return rs->toString() + " -> [$fp - " + LL2W::toString(imm, false) + ']';
	}

	Instruction * SpsIInstruction::copy() const {
		return new SpsIInstruction(*this);
	}
}
