#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** %time $rs */
	struct TimeRInstruction: RType {
		TimeRInstruction(VariablePtr rs_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
