#pragma once

#include "instruction/LinkedSD.h"
#include "instruction/RType.h"

namespace LL2W {
	/** $rs << $rt -> $rd */
	struct ShiftLeftLogicalRInstruction: LinkedSD<RType> {
		using LinkedSD::LinkedSD;
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
