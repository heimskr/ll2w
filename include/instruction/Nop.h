#pragma once

#include "instruction/WhyInstruction.h"

namespace LL2W {
	struct Nop: WhyInstruction {
		Nop(int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
