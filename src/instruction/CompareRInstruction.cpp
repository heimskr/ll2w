#include "compiler/Variable.h"
#include "instruction/CompareRInstruction.h"

namespace LL2W {
	CompareRInstruction::CompareRInstruction(VariablePtr rs_, VariablePtr rt_, int index_):
		RType(rs_, rt_, nullptr, index_) {}

	std::string CompareRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m~\e[22m " + std::string(*rt);
	}

	std::string CompareRInstruction::toString() const {
		return rs->toString() + " ~ " + rt->toString();
	}
}
