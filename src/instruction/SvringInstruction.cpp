#include "compiler/Variable.h"
#include "instruction/SvringInstruction.h"

namespace LL2W {
	SvringInstruction::SvringInstruction(VariablePtr rd_, int index_):
		RType(nullptr, nullptr, std::move(rd_), index_) {}

	std::string SvringInstruction::debugExtra() const {
		return "\e[36m%ring\e[39m \e[2m->\e[22m " + std::string(*rd);
	}

	std::string SvringInstruction::toString() const {
		return "%ring -> " + rd->toString();
	}
	
	Instruction * SvringInstruction::copy() const {
		return new SvringInstruction(*this);
	}
}
