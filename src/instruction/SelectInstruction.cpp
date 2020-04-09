#include "compiler/Variable.h"
#include "instruction/SelectInstruction.h"

namespace LL2W {
	const std::unordered_map<Condition, const char *> SelectInstruction::operMap {
		{Condition::Zero, "="},
		{Condition::Positive, ">"},
		{Condition::Negative, "<"},
		{Condition::Nonzero, "!="},
	};

	std::string SelectInstruction::debugExtra() {
		return "\e[2m[\e[22m" + std::string(*rs) + " " + std::string(operMap.at(condition)) + " " + std::string(*rt) +
			"\e[2m] ->\e[22m " + std::string(*rd);
	}

	std::string SelectInstruction::toString() const {
		return "[" + rs->toString() + " " + std::string(operMap.at(condition)) + " " + rt->toString() + "] -> " +
			rd->toString();
	}
}
