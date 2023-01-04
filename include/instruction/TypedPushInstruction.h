#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** #[ $rs */
	struct TypedPushInstruction: RType {
		TypedPushInstruction(VariablePtr rs_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
