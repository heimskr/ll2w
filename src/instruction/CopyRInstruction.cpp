#include "compiler/Variable.h"
#include "instruction/CopyRInstruction.h"

namespace LL2W {
	CopyRInstruction::CopyRInstruction(VariablePtr rs, VariablePtr rd, WASMSize size):
		RType(std::move(rs), nullptr, std::move(rd)),
		HasSize(size) {}

	std::string CopyRInstruction::debugExtra() const {
		return "\e[2m[\e[22m" + std::string(*rs) + "\e[2m] -> [\e[22m " + std::string(*rd) + "\e[2m]\e[22m" + sizeSuffix();
	}

	std::string CopyRInstruction::toString() const {
		return "[" + rs->toString() + "] -> [" + rd->toString() + "]" + sizeSuffix();
	}

	bool CopyRInstruction::fixSignedness() {
		return rs->type->shareSignedness(rd->type);
	}

	Instruction * CopyRInstruction::copy() const {
		return new CopyRInstruction(*this);
	}
}
