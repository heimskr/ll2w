#pragma once

#include "instruction/HasSize.h"
#include "instruction/LinkedSD.h"
#include "instruction/RType.h"

namespace LL2W {
	/** [$rs] -> $rd */
	struct LoadRInstruction: LinkedSD<RType>, HasSize {
		LoadRInstruction(VariablePtr rs, VariablePtr rd, WASMSize);

		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
