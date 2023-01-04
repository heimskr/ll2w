#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** %setpt $rs
	 *  : %setpt $rs $rt */
	struct SetptRInstruction: RType {
		SetptRInstruction(VariablePtr rs_, VariablePtr rt_, int index_ = -1);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
