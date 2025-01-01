#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** Copies one register into a subregister of a variable. Needs to be replaced with a move instruction after
	 *  register allocation has been done. */
	struct DeferredDestinationMoveInstruction: RType {
		int registerIndex;

		DeferredDestinationMoveInstruction(VariablePtr rs_, VariablePtr rd_, int register_index);

		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
