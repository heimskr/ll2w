#include "compiler/Variable.h"
#include "instruction/RingRInstruction.h"

namespace LL2W {
	RingRInstruction::RingRInstruction(std::shared_ptr<Variable> rs_, int index_):
		RType(rs_, nullptr, nullptr, index_) {}

	std::string RingRInstruction::debugExtra() {
		return "\e[36mring\e[39m " + std::string(*rs);
	}

	std::string RingRInstruction::toString() const {
		return "ring " + rs->toString();
	}
}
