#pragma once

#include "instruction/LinkedSTD.h"

namespace LL2W {
	struct LogicalNotRInstruction: LinkedSTD<> {
		LogicalNotRInstruction(VariablePtr rs_, VariablePtr rd_):
			LinkedSTD(std::move(rs_), nullptr, std::move(rd_)) {}

		LogicalNotRInstruction(const VariablePtr &rs_):
			LinkedSTD(rs_, nullptr, rs_) {}

		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
