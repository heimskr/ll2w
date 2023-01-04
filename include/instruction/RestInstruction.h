#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct RestInstruction: RType {
		RestInstruction(int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
