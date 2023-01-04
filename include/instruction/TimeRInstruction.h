#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** %time $rs */
	struct TimeRInstruction: RType {
		TimeRInstruction(VariablePtr rs_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
