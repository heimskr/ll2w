#include "compiler/Variable.h"
#include "instruction/CompareRInstruction.h"

namespace LL2W {
	CompareRInstruction::CompareRInstruction(VariablePtr rs_, VariablePtr rt_):
		RType(rs_, rt_, nullptr) {}

	std::string CompareRInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m~\e[22m " + std::string(*rt);
	}

	std::string CompareRInstruction::toString() const {
		return rs->toString() + " ~ " + rt->toString();
	}

	Instruction * CompareRInstruction::copy() const {
		return new CompareRInstruction(*this);
	}
}
