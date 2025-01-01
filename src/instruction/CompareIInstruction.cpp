#include "compiler/Variable.h"
#include "instruction/CompareIInstruction.h"

namespace LL2W {
	CompareIInstruction::CompareIInstruction(VariablePtr rs, Immediate imm):
		IType(std::move(rs), std::move(imm), nullptr) {}

	std::string CompareIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m~\e[22m " + colorize(imm, *rs);
	}

	std::string CompareIInstruction::toString() const {
		return rs->toString() + " ~ " + LL2W::toString(imm);
	}

	Instruction * CompareIInstruction::copy() const {
		return new CompareIInstruction(*this);
	}
}
