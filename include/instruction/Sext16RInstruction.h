#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct Sext16RInstruction: public RType {
		Sext16RInstruction(VariablePtr rs_, VariablePtr rd_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
