#pragma once

#include "instruction/LinkedSTD.h"

namespace LL2W {
	struct LogicalNotRInstruction: LinkedSTD<> {
		LogicalNotRInstruction(VariablePtr rs_, VariablePtr rd_, int index_ = -1):
			LinkedSTD(std::move(rs_), nullptr, std::move(rd_), index_) {}

		LogicalNotRInstruction(const VariablePtr &rs_, int index_ = -1):
			LinkedSTD(rs_, nullptr, rs_, index_) {}

		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
