#include "compiler/Variable.h"
#include "instruction/ComparisonIInstruction.h"

namespace LL2W {
	std::string ComparisonIInstruction::debugExtra() {
		return std::string(*rs) + " \e[2m" + cond_op_map_with_sign.at(cond) + "\e[22m " + colorize(imm, *rs) +
			" \e[2m->\e[22m " + std::string(*rd);
	}

	std::string ComparisonIInstruction::toString() const {
		return rs->toString() + " " + cond_op_map.at(cond) + " " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}

	bool ComparisonIInstruction::fixSignedness() {
		const bool out = rd->setSigned(false);
		// const bool out = false;
		if (signed_conds.contains(cond))
			return rs->setSigned(true) || out;
		if (unsigned_conds.contains(cond))
			return rs->setSigned(false) || out;
		return out;
	}
}
