#include "compiler/Variable.h"
#include "instruction/MultIInstruction.h"

namespace LL2W {
	/** $rs * imm */
	MultIInstruction::MultIInstruction(VariablePtr rs, Immediate imm):
		IType(std::move(rs), std::move(imm), nullptr) {}

	std::string MultIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m*\e[22m " + colorize(imm, *rs);
	}

	std::string MultIInstruction::toString() const {
		return rs->toString() + " * " + LL2W::toString(imm);
	}

	Instruction * MultIInstruction::copy() const {
		return new MultIInstruction(*this);
	}
}
