#include "compiler/Variable.h"
#include "instruction/ComparisonIInstruction.h"

namespace LL2W {
	std::string ComparisonIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m" + cond_op_map.at(cond) + "\e[22m " + colorize(imm, *rs) + " \e[2m->\e[22m "
			+ std::string(*rd);
	}

	std::string ComparisonIInstruction::toString() const {
		return rs->toString() + " " + cond_op_map.at(cond) + " " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}

	void ComparisonIInstruction::fixSignedness() {
		rd->setSigned(false);
		if (signed_conds.contains(cond))
			rs->setSigned(true);
		else if (unsigned_conds.contains(cond))
			rs->setSigned(false);
	}
}
