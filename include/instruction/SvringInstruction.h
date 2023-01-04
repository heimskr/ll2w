#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** %ring -> $rd */
	struct SvringInstruction: RType {
		SvringInstruction(VariablePtr rd_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
