#pragma once

#include "instruction/ComparisonInstruction.h"
#include "instruction/RType.h"
#include "parser/Enums.h"

#include <unordered_map>

namespace LL2W {
	/** $rs == (<=, <...) $rt -> $rd */
	struct ComparisonRInstruction: RType, ComparisonInstruction {
		ComparisonRInstruction(VariablePtr rs, VariablePtr rt, VariablePtr rd, IcmpCond cond):
			RType(std::move(rs), std::move(rt), std::move(rd)),
			ComparisonInstruction(cond) {}

		std::string debugExtra() const override;
		std::string toString() const override;
		bool fixSignedness() override;
		Instruction * copy() const override;
		bool typeMismatch() const override;
	};
}
