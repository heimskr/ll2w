#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct MultRInstruction: public RType {
		MultRInstruction(VariablePtr rs_, VariablePtr rt_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
