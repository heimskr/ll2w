#include "compiler/Variable.h"
#include "instruction/ComparisonRInstruction.h"

namespace LL2W {
	std::string ComparisonRInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m" + cond_op_map.at(cond) + "\e[22m " + std::string(*rt) + " \e[2m->\e[22m "
			+ std::string(*rd);
	}

	std::string ComparisonRInstruction::toString() const {
		return rs->toString() + " " + cond_op_map.at(cond) + " " + rt->toString() + " -> " + rd->toString();
	}

	void ComparisonRInstruction::fixSignedness() {
		rd->setSigned(false);
		if (signed_conds.contains(cond)) {
			rs->setSigned(true);
			rt->setSigned(true);
		} else if (unsigned_conds.contains(cond)) {
			rs->setSigned(false);
			rt->setSigned(false);
		}
	}
}
