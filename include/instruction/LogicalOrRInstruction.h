#pragma once

#include "instruction/LinkedSTD.h"

namespace LL2W {
	struct LogicalOrRInstruction: LinkedSTD<> {
		using LinkedSTD::LinkedSTD;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
