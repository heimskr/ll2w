#include "compiler/Variable.h"
#include "instruction/CompareIInstruction.h"

namespace LL2W {
	CompareIInstruction::CompareIInstruction(VariablePtr rs_, int imm_, int index_):
		IType(rs_, imm_, nullptr, index_) {}

	std::string CompareIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m~\e[0m " + std::to_string(imm);
	}

	std::string CompareIInstruction::toString() const {
		return rs->toString() + " ~ " + std::to_string(imm);
	}
}
