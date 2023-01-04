#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/**
	 * [$rs] -> [$rd]
	 */
	struct CopyRInstruction: RType {
		CopyRInstruction(VariablePtr rs_, VariablePtr rd_, int index_ = -1);

		std::string debugExtra() const override;
		std::string toString() const override;
		bool fixSignedness() override;
		Instruction * copy() const override;
	};
}
