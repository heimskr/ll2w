#include "compiler/Variable.h"
#include "instruction/CompareIInstruction.h"

namespace LL2W {
	CompareIInstruction::CompareIInstruction(VariablePtr rs_, Immediate imm_, int index_):
		IType(std::move(rs_), std::move(imm_), nullptr, index_) {}

	std::string CompareIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m~\e[22m " + colorize(imm, *rs);
	}

	std::string CompareIInstruction::toString() const {
		return rs->toString() + " ~ " + LL2W::toString(imm, *rs);
	}
	
	Instruction * CompareIInstruction::copy() const {
		return new CompareIInstruction(*this);
	}
}
