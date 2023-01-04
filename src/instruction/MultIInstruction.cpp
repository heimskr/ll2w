#include "compiler/Variable.h"
#include "instruction/MultIInstruction.h"

namespace LL2W {
	/** $rs * imm */
	MultIInstruction::MultIInstruction(VariablePtr rs_, ValueType imm_, int index_):
		IType(std::move(rs_), std::move(imm_), nullptr, index_) {}

	std::string MultIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m*\e[0m " + colorize(imm, *rs);
	}

	std::string MultIInstruction::toString() const {
		return rs->toString() + " * " + LL2W::toString(imm, *rs);
	}
	
	Instruction * MultIInstruction::copy() const {
		return new MultIInstruction(*this);
	}
}
