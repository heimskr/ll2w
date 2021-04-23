#include "compiler/Variable.h"
#include "instruction/SleepRInstruction.h"

namespace LL2W {
	SleepRInstruction::SleepRInstruction(std::shared_ptr<Variable> rs_, int index_):
		RType(rs_, nullptr, nullptr, index_) {}

	std::string SleepRInstruction::debugExtra() {
		return "<\e[36msleep\e[39m " + std::string(*rs) + ">";
	}

	std::string SleepRInstruction::toString() const {
		return "<sleep " + rs->toString() + ">";
	}
}
