#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct RestInstruction: RType {
		RestInstruction();
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
