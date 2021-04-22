#include "instruction/Conditional.h"

namespace LL2W {
	Conditional::Conditional(Condition condition_): condition(condition_) {}

	std::string Conditional::conditionPrefix() const {
		switch (condition) {
			case Condition::Zero:     return "0";
			case Condition::Negative: return "-";
			case Condition::Positive: return "+";
			case Condition::Nonzero:  return "*";
			default: return "";
		}
	}
}
