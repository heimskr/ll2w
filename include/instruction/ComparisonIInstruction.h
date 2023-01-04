#pragma once

#include "instruction/ComparisonInstruction.h"
#include "instruction/IType.h"
#include "parser/Enums.h"

#include <unordered_map>

namespace LL2W {
	/** $rs == (<=, <...) $rt -> $rd */
	struct ComparisonIInstruction: IType, ComparisonInstruction {
		ComparisonIInstruction(VariablePtr rs_, Immediate imm_, VariablePtr rd_, IcmpCond cond_, int index_ = -1):
			IType(rs_, imm_, rd_, index_), ComparisonInstruction(cond_) {}

		std::string debugExtra() override;
		std::string toString() const override;
		bool fixSignedness() override;
		Instruction * copy() const override;
	};
}
