#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** translate $rs -> $rd */
	struct TranslateAddressRInstruction: RType, Makeable<TranslateAddressRInstruction> {
		TranslateAddressRInstruction(VariablePtr rs_, VariablePtr rd_, int index_ = -1);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
