#pragma once

#include "instruction/LinkedSTD.h"

namespace LL2W {
	struct LogicalXorRInstruction: LinkedSTD<> {
		using LinkedSTD::LinkedSTD;
		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
