#include "compiler/Variable.h"
#include "instruction/RingIInstruction.h"

namespace LL2W {
	RingIInstruction::RingIInstruction(ValueType imm_, int index_):
		IType(nullptr, std::move(imm_), nullptr, index_) {}

	std::string RingIInstruction::debugExtra() {
		return "\e[36m%ring\e[39m " + colorize(imm);
	}

	std::string RingIInstruction::toString() const {
		return "%ring " + LL2W::toString(imm);
	}
}
