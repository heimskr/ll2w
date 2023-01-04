#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct AndRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() const override;
		std::string toString() const override;
		bool fixSignedness() override;
		Instruction * copy() const override;
	};
}
