#pragma once

#include "instruction/LinkedSD.h"
#include "instruction/RType.h"

namespace LL2W {
	struct SextRInstruction: LinkedSD<RType> {
		SextRInstruction(VariablePtr rs, VariablePtr rd);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
