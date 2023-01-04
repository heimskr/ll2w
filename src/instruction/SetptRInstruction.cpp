#include "compiler/Variable.h"
#include "instruction/SetptRInstruction.h"

namespace LL2W {
	SetptRInstruction::SetptRInstruction(VariablePtr rs_, VariablePtr rt_, int index_):
		RType(std::move(rs_), std::move(rt_), nullptr, index_) {}

	std::string SetptRInstruction::debugExtra() const {
		if (!rt)
			return "\e[36m%setpt\e[39m " + std::string(*rs);
		return "\e[2m:\e[22m \e[36m%setpt\e[39m " + std::string(*rs) + " " + std::string(*rt);
	}

	std::string SetptRInstruction::toString() const {
		if (!rt)
			return "%setpt " + rs->toString();
		return ": %setpt " + rs->toString() + " " + rt->toString();
	}
	
	Instruction * SetptRInstruction::copy() const {
		return new SetptRInstruction(*this);
	}
}
