#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** Copies one subregister of a variable into another register. Needs to be replaced with a move instruction after
	 *  register allocation has been done. */
	struct DeferredSourceMoveInstruction: RType {
		int registerIndex;

		DeferredSourceMoveInstruction(VariablePtr rs_, VariablePtr rd_, int register_index, int index_ = -1);

		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
