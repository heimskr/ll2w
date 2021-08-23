#include "compiler/Variable.h"
#include "instruction/SetptRInstruction.h"

namespace LL2W {
	std::string SetptRInstruction::debugExtra() {
		return "\e[36m%setpt\e[39m " + std::string(*rs);
	}

	std::string SetptRInstruction::toString() const {
		return "%setpt " + rs->toString();
	}
}
