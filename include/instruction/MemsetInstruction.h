#pragma once

#include "instruction/LinkedSD.h"
#include "instruction/ThreeSourcesRType.h"

namespace LL2W {
	struct MemsetInstruction: LinkedSD<ThreeSourcesRType> {
		using LinkedSD::LinkedSD;
		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
