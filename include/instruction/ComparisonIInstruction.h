#pragma once

#include "instruction/ComparisonInstruction.h"
#include "instruction/IType.h"
#include "parser/Enums.h"

#include <unordered_map>

namespace LL2W {
	/**
	 * $rs == (<=, <...) $rt -> $rd (/u)
	 */
	struct ComparisonIInstruction: IType, ComparisonInstruction {
		ComparisonIInstruction(VariablePtr rs, Immediate imm, VariablePtr rd, IcmpCond cond):
			IType(std::move(rs), std::move(imm), std::move(rd)),
			ComparisonInstruction(cond) {}

		std::string debugExtra() const override;
		std::string toString() const override;
		bool fixSignedness() override;
		Instruction * copy() const override;
		bool typeMismatch() const override;
	};
}
