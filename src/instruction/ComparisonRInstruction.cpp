#include "compiler/Variable.h"
#include "instruction/ComparisonRInstruction.h"

namespace LL2W {
	std::string ComparisonRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m" + cond_op_map_with_sign.at(cond) + "\e[22m " + std::string(*rt) +
			" \e[2m->\e[22m " + std::string(*rd);
	}

	std::string ComparisonRInstruction::toString() const {
		return rs->toString() + " " + cond_op_map.at(cond) + " " + rt->toString() + " -> " + rd->toString();
	}

	bool ComparisonRInstruction::fixSignedness() {
		bool out = rd->setSigned(false);
		if (signed_conds.contains(cond)) {
			out = rs->setSigned(true) || out;
			out = rt->setSigned(true) || out;
		} else if (unsigned_conds.contains(cond)) {
			out = rs->setSigned(false) || out;
			out = rt->setSigned(false) || out;
		}
		return out;
	}
	
	Instruction * ComparisonRInstruction::copy() const {
		return new ComparisonRInstruction(*this);
	}
}
