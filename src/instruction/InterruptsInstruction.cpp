#include "compiler/Variable.h"
#include "instruction/InterruptsInstruction.h"

namespace LL2W {
	InterruptsInstruction::InterruptsInstruction(bool enable):
		RType(nullptr, nullptr, nullptr), enable(enable) {}

	std::string InterruptsInstruction::debugExtra() const {
		return "\e[34m" + std::string(enable? "%ei" : "%di") + "\e[39m";
	}

	std::string InterruptsInstruction::toString() const {
		return enable? "%ei" : "%di";
	}

	Instruction * InterruptsInstruction::copy() const {
		return new InterruptsInstruction(*this);
	}
}
