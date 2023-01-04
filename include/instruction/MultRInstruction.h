#pragma once

#include "instruction/LinkedST.h"

namespace LL2W {
	/** $rs * $rt */
	struct MultRInstruction: LinkedST<>, Makeable<MultRInstruction> {
		MultRInstruction(VariablePtr rs_, VariablePtr rt_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
