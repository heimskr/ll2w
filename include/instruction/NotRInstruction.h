#pragma once

#include "instruction/LinkedSD.h"
#include "instruction/RType.h"

namespace LL2W {
	struct NotRInstruction: LinkedSD<RType> {
		NotRInstruction(VariablePtr rs_, VariablePtr rd_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
