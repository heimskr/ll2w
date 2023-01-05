#include "compiler/Variable.h"
#include "instruction/ComparisonIInstruction.h"

namespace LL2W {
	std::string ComparisonIInstruction::debugExtra() const {
		return std::string(*rs) + " \e[2m" + cond_op_map_with_sign.at(cond) + "\e[22m " + colorize(imm, *rs) +
			" \e[2m->\e[22m " + std::string(*rd);
	}

	std::string ComparisonIInstruction::toString() const {
		return rs->toString() + " " + cond_op_map.at(cond) + " " + LL2W::toString(imm, *rs) + " -> " + rd->toString();
	}

	bool ComparisonIInstruction::fixSignedness() {
		const bool out = rd->setSigned(false);
		if (signed_conds.contains(cond))
			return rs->setSigned(true) || out;
		if (unsigned_conds.contains(cond))
			return rs->setSigned(false) || out;
		return out;
	}
	
	Instruction * ComparisonIInstruction::copy() const {
		return new ComparisonIInstruction(*this);
	}

	bool ComparisonIInstruction::typeMismatch() const {
		if (rs->isVoid())
			return false;

		if (signed_conds.contains(cond)) {
			if (rs->getSignedness() == Signedness::Unsigned)
				return true;
		} else if (unsigned_conds.contains(cond)) {
			if (rs->getSignedness() == Signedness::Signed)
				return true;
		}

		return false;
	}
}
