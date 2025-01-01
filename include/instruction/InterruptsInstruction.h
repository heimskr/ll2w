#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct InterruptsInstruction: RType {
		bool enable{};

		InterruptsInstruction(bool enable);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
