#include "compiler/Variable.h"
#include "instruction/SvtimeInstruction.h"

namespace LL2W {
	SvtimeInstruction::SvtimeInstruction(VariablePtr rd_, int index_):
		RType(nullptr, nullptr, std::move(rd_), index_) {}

	std::string SvtimeInstruction::debugExtra() const {
		return "\e[36m%time\e[39m \e[2m->\e[22m " + std::string(*rd);
	}

	std::string SvtimeInstruction::toString() const {
		return "%time -> " + rd->toString();
	}
	
	Instruction * SvtimeInstruction::copy() const {
		return new SvtimeInstruction(*this);
	}
}
