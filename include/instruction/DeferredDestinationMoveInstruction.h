#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** Copies one register into a subregister of a variable. Needs to be replaced with a move instruction after
	 *  register allocation has been done. */
	struct DeferredDestinationMoveInstruction: RType {
		int registerIndex;

		DeferredDestinationMoveInstruction(VariablePtr rs_, VariablePtr rd_, int register_index, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
