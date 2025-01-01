#pragma once

#include "instruction/LinkedST.h"

namespace LL2W {
	/** $rs * $rt */
	struct MultRInstruction: LinkedST<>, Makeable<MultRInstruction> {
		MultRInstruction(VariablePtr rs_, VariablePtr rt_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
