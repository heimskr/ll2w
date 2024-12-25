#pragma once

#include "instruction/HasSize.h"
#include "instruction/RType.h"

namespace LL2W {
	/**
	 * [$rs] -> [$rd]
	 */
	struct CopyRInstruction: RType, HasSize {
		CopyRInstruction(VariablePtr rs, VariablePtr rd, WASMSize);

		std::string debugExtra() const override;
		std::string toString() const override;
		bool fixSignedness() override;
		Instruction * copy() const override;
	};
}
