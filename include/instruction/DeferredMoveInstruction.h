#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** Copies one register into a subregister of a variable. Needs to be replaced with a move instruction after
	 *  register allocation has been done. */
	struct DeferredMoveInstruction: public RType {
		int registerIndex;

		DeferredMoveInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_, int register_index,
		int index_ = -1):
			RType(rs_, nullptr, rd_, index_), registerIndex(register_index) {}

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
