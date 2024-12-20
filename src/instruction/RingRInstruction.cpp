#include "compiler/Variable.h"
#include "instruction/RingRInstruction.h"

namespace LL2W {
	RingRInstruction::RingRInstruction(std::shared_ptr<Variable> rs_, int index_):
		RType(std::move(rs_), nullptr, nullptr, index_) {}

	std::string RingRInstruction::debugExtra() const {
		return "\e[36m%ring\e[39m " + std::string(*rs);
	}

	std::string RingRInstruction::toString() const {
		return "%ring " + rs->toString();
	}
	
	Instruction * RingRInstruction::copy() const {
		return new RingRInstruction(*this);
	}
}
