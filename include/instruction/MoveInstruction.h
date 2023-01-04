#pragma once

#include "instruction/LinkedSD.h"
#include "instruction/RType.h"

namespace LL2W {
	/** Copies one register into another. */
	struct MoveInstruction: LinkedSD<RType>, Makeable<MoveInstruction> {
		MoveInstruction(VariablePtr rs_, VariablePtr rd_, int index_ = -1):
			LinkedSD(rs_, nullptr, rd_, index_) {}

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
