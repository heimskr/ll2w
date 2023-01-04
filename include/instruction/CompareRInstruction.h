#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** $rs ~ $rt */
	struct CompareRInstruction: public RType {
		CompareRInstruction(VariablePtr rs_, VariablePtr rt_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
