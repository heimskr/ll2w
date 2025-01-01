#include "compiler/Variable.h"
#include "instruction/SvpgInstruction.h"

namespace LL2W {
	SvpgInstruction::SvpgInstruction(VariablePtr rd_):
		RType(nullptr, nullptr, std::move(rd_)) {}

	std::string SvpgInstruction::debugExtra() const {
		return "\e[36m%page\e[39m \e[2m->\e[22m " + std::string(*rd);
	}

	std::string SvpgInstruction::toString() const {
		return "%page -> " + rd->toString();
	}

	Instruction * SvpgInstruction::copy() const {
		return new SvpgInstruction(*this);
	}
}
