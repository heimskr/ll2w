#include "compiler/Variable.h"
#include "instruction/CopyRInstruction.h"

namespace LL2W {
	CopyRInstruction::CopyRInstruction(const std::shared_ptr<Variable> &rs_, const std::shared_ptr<Variable> &rd_,
	int index_):
		RType(rs_, nullptr, rd_, index_) {}

	std::string CopyRInstruction::debugExtra() {
		return "\e[2m[\e[22m" + std::string(*rs) + "\e[2m] -> [\e[22m " + std::string(*rd) + "\e[2m]\e[22m";
	}

	std::string CopyRInstruction::toString() const {
		return "[" + rs->toString() + "] -> [" + rd->toString() + "]";
	}

	bool CopyRInstruction::fixSignedness() {
		return rs->type->shareSignedness(rd->type);
	}
}
