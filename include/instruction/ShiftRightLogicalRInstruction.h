#pragma once

#include "instruction/LinkedSD.h"
#include "instruction/RType.h"

namespace LL2W {
	struct ShiftRightLogicalRInstruction: LinkedSD<RType> {
		using LinkedSD::LinkedSD;
		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
