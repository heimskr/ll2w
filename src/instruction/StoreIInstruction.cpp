#include "compiler/Variable.h"
#include "instruction/StoreIInstruction.h"

namespace LL2W {
	StoreIInstruction::StoreIInstruction(VariablePtr rs_, ValueType imm_, int index_):
		IType(std::move(rs_), std::move(imm_), nullptr, index_) {}

	std::string StoreIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m-> [\e[22;91m" + colorize(imm, *rs, 1) + "\e[39;2m]\e[22m";
	}

	std::string StoreIInstruction::toString() const {
		return rs->toString() + " -> [" + LL2W::toString(imm, *rs, 1) + "]";
	}
}
