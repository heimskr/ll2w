#pragma once

#include "instruction/LinkedSD.h"
#include "instruction/RType.h"

namespace LL2W {
	struct NotRInstruction: LinkedSD<RType> {
		NotRInstruction(VariablePtr rs_, VariablePtr rd_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
