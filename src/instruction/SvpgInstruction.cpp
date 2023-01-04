#include "compiler/Variable.h"
#include "instruction/SvpgInstruction.h"

namespace LL2W {
	SvpgInstruction::SvpgInstruction(VariablePtr rd_, int index_):
		RType(nullptr, nullptr, std::move(rd_), index_) {}

	std::string SvpgInstruction::debugExtra() {
		return "\e[36m%page\e[39m \e[2m->\e[22m " + std::string(*rd);
	}

	std::string SvpgInstruction::toString() const {
		return "%page -> " + rd->toString();
	}
}
