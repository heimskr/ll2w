#include "compiler/Variable.h"
#include "instruction/InterruptsInstruction.h"

namespace LL2W {
	InterruptsInstruction::InterruptsInstruction(bool enable_, int index_):
		RType(nullptr, nullptr, nullptr, index_), enable(enable_) {}

	std::string InterruptsInstruction::debugExtra() {
		return "\e[34m" + std::string(enable? "%ei" : "%di") + "\e[39m";
	}

	std::string InterruptsInstruction::toString() const {
		return enable? "%ei" : "%di";
	}
	
	Instruction * InterruptsInstruction::copy() const {
		return new InterruptsInstruction(*this);
	}
}
