#pragma once

#include "instruction/LinkedSTD.h"

namespace LL2W {
	struct LogicalXnorRInstruction: LinkedSTD<> {
		using LinkedSTD::LinkedSTD;
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
