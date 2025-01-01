#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** <sleep $rs> */
	struct SleepRInstruction: RType {
		SleepRInstruction(VariablePtr rs_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
