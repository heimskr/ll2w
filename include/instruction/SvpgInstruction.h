#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** %page -> $rd */
	struct SvpgInstruction: RType {
		SvpgInstruction(VariablePtr rd_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
