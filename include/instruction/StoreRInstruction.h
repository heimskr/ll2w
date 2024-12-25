#pragma once

#include "instruction/HasSize.h"
#include "instruction/LinkedST.h"
#include "instruction/RType.h"

namespace LL2W {
	/** $rs -> [$rt] */
	struct StoreRInstruction: LinkedST<>, HasSize {
		StoreRInstruction(VariablePtr rs, VariablePtr rt, WASMSize);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
