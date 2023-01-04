#include "compiler/Variable.h"
#include "instruction/SleepRInstruction.h"

namespace LL2W {
	SleepRInstruction::SleepRInstruction(VariablePtr rs_, int index_):
		RType(std::move(rs_), nullptr, nullptr, index_) {}

	std::string SleepRInstruction::debugExtra() const {
		return "<\e[36msleep\e[39m " + std::string(*rs) + ">";
	}

	std::string SleepRInstruction::toString() const {
		return "<sleep " + rs->toString() + ">";
	}
	
	Instruction * SleepRInstruction::copy() const {
		return new SleepRInstruction(*this);
	}
}
