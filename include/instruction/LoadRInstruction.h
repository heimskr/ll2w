#pragma once

#include "instruction/LinkedSD.h"
#include "instruction/RType.h"

namespace LL2W {
	/** [$rs] -> $rd */
	struct LoadRInstruction: LinkedSD<RType> {
		LoadRInstruction(VariablePtr rs_, VariablePtr rd_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
