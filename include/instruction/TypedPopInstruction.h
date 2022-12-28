#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct TypedPopInstruction: public RType {
		TypedPopInstruction(const VariablePtr &rd_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
