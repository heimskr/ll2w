#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** %time -> $rd */
	struct SvtimeInstruction: RType {
		SvtimeInstruction(VariablePtr rd_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
