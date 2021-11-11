#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct Sext32RInstruction: public RType {
		Sext32RInstruction(VariablePtr rs_, VariablePtr rd_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
