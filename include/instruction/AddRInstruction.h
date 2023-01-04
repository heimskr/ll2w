#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct AddRInstruction: RType, Makeable<AddRInstruction> {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
		bool fixSignedness() override;
		Instruction * copy() const override;
	};
}
