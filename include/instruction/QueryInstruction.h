#pragma once

#include "instruction/RType.h"
#include "parser/Enums.h"

namespace LL2W {
	/** ? type -> $rd */
	struct QueryInstruction: RType {
		QueryType type;
		QueryInstruction(QueryType, VariablePtr rd_, int index_ = -1);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
