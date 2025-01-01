#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** $rs ~ $rt */
	struct CompareRInstruction: public RType {
		CompareRInstruction(VariablePtr rs_, VariablePtr rt_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
