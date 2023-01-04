#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** %page -> $rd */
	struct SvpgInstruction: RType {
		SvpgInstruction(VariablePtr rd_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
