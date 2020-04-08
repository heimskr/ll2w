#include "compiler/Variable.h"
#include "instruction/ComparisonRInstruction.h"

namespace LL2W {
	std::string ComparisonRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m" + cond_op_map.at(cond) + "\e[22m " + std::string(*rt) + " \e[2m->\e[22m "
			+ std::string(*rd) + (isUnsigned()? " \e[2m/u\e[22m" : "");
	}

	std::string ComparisonRInstruction::toString() const {
		return rs->toString() + " " + cond_op_map.at(cond) + " " + rt->toString() + " -> " + rd->toString()
			+ (isUnsigned()? " /u" : "");
	}
}
