#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct HaltInstruction: RType {
		HaltInstruction();
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
