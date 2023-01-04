#include "compiler/Variable.h"
#include "instruction/CopyRInstruction.h"

namespace LL2W {
	CopyRInstruction::CopyRInstruction(VariablePtr rs_, VariablePtr rd_, int index_):
		RType(std::move(rs_), nullptr, std::move(rd_), index_) {}

	std::string CopyRInstruction::debugExtra() const {
		return "\e[2m[\e[22m" + std::string(*rs) + "\e[2m] -> [\e[22m " + std::string(*rd) + "\e[2m]\e[22m";
	}

	std::string CopyRInstruction::toString() const {
		return "[" + rs->toString() + "] -> [" + rd->toString() + "]";
	}

	bool CopyRInstruction::fixSignedness() {
		return rs->type->shareSignedness(rd->type);
	}
	
	Instruction * CopyRInstruction::copy() const {
		return new CopyRInstruction(*this);
	}
}
