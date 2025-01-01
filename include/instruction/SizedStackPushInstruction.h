#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct SizedStackPushInstruction: RType {
		int size; // in bytes
		SizedStackPushInstruction(VariablePtr rs, int size_);
		SizedStackPushInstruction(VariablePtr rs);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
