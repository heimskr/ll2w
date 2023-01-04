#include "compiler/Variable.h"
#include "instruction/RingIInstruction.h"

namespace LL2W {
	RingIInstruction::RingIInstruction(Immediate imm_, int index_):
		IType(nullptr, std::move(imm_), nullptr, index_) {}

	std::string RingIInstruction::debugExtra() const {
		return "\e[36m%ring\e[39m " + colorize(imm);
	}

	std::string RingIInstruction::toString() const {
		return "%ring " + LL2W::toString(imm);
	}
	
	Instruction * RingIInstruction::copy() const {
		return new RingIInstruction(*this);
	}
}
