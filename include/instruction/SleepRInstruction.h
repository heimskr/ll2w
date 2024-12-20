#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** <sleep $rs> */
	struct SleepRInstruction: RType {
		SleepRInstruction(VariablePtr rs_, int index_ = -1);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
