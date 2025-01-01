#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** [ $rs */
	struct StackPushInstruction: RType {
		StackPushInstruction(VariablePtr rs_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
