#pragma once

#include "instruction/ComparisonInstruction.h"
#include "instruction/RType.h"
#include "parser/Enums.h"

#include <unordered_map>

namespace LL2W {
	/** $rs == (<=, <...) $rt -> $rd */
	struct ComparisonRInstruction: RType, ComparisonInstruction {
		ComparisonRInstruction(VariablePtr rs_, VariablePtr rt_, VariablePtr rd_, IcmpCond cond_, int index_ = -1):
			RType(rs_, rt_, rd_, index_), ComparisonInstruction(cond_) {}

		std::string debugExtra() override;
		std::string toString() const override;
		bool fixSignedness() override;
		Instruction * copy() const override;
	};
}
