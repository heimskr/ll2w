#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct PageInstruction: RType {
		bool on;

		PageInstruction(bool, int index_ = -1);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
