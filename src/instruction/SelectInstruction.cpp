#include "compiler/Variable.h"
#include "instruction/SelectInstruction.h"

namespace LL2W {
	const std::unordered_map<Condition, const char *> SelectInstruction::operMap {
		{Condition::Zero,     "="},
		{Condition::Positive, ">"},
		{Condition::Negative, "<"},
		{Condition::Nonzero,  "!="},
	};

	SelectInstruction::SelectInstruction(VariablePtr rs, VariablePtr rt, VariablePtr rd, Condition condition):
		RType(std::move(rs), std::move(rt), std::move(rd)),
		condition(condition) {}

	std::string SelectInstruction::debugExtra() const {
		return "\e[2m[\e[22m" + std::string(*rs) + " " + std::string(operMap.at(condition)) + " " + std::string(*rt) +
			"\e[2m] ->\e[22m " + std::string(*rd);
	}

	std::string SelectInstruction::toString() const {
		return "[" + rs->toString() + " " + std::string(operMap.at(condition)) + " " + rt->toString() + "] -> " +
			rd->toString();
	}

	Instruction * SelectInstruction::copy() const {
		return new SelectInstruction(*this);
	}
}
