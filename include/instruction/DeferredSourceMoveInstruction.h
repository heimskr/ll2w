#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** Copies one subregister of a variable into another register. Needs to be replaced with a move instruction after
	 *  register allocation has been done. */
	struct DeferredSourceMoveInstruction: RType {
		int registerIndex = -1;

		DeferredSourceMoveInstruction(VariablePtr rs, VariablePtr rd, int register_index);

		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
