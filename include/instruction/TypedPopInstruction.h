#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** #] $rd */
	struct TypedPopInstruction: RType {
		TypedPopInstruction(VariablePtr rd_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
