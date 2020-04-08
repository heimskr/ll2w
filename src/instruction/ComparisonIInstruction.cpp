#include "compiler/Variable.h"
#include "instruction/ComparisonIInstruction.h"

namespace LL2W {
	std::string ComparisonIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m" + cond_op_map.at(cond) + "\e[22m " + std::to_string(imm) + " \e[2m->\e[22m "
			+ std::string(*rd) + (isUnsigned()? " \e[2m/u\e[22m" : "");
	}

	std::string ComparisonIInstruction::toString() const {
		return rs->toString() + " " + cond_op_map.at(cond) + " " + std::to_string(imm) + " -> " + rd->toString()
			+ (isUnsigned()? " /u" : "");
	}
}
