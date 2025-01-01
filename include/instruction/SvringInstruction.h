#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** %ring -> $rd */
	struct SvringInstruction: RType {
		SvringInstruction(VariablePtr rd_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
