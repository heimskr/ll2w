#include "compiler/Variable.h"
#include "instruction/TimeRInstruction.h"

namespace LL2W {
	TimeRInstruction::TimeRInstruction(std::shared_ptr<Variable> rs_, int index_):
		RType(rs_, nullptr, nullptr, index_) {}

	std::string TimeRInstruction::debugExtra() {
		return "\e[36m%time\e[39m " + std::string(*rs);
	}

	std::string TimeRInstruction::toString() const {
		return "%time " + rs->toString();
	}
}
