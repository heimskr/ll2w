#pragma once

#include "compiler/StackLocation.h"
#include "instruction/IntermediateInstruction.h"

namespace LL2W {
	struct StackLoadInstruction: IntermediateInstruction {
		VariablePtr result;
		StackLocation location;

		StackLoadInstruction(VariablePtr result, StackLocation location):
			result(std::move(result)),
			location(std::move(location)) {}

		ExtractionResult extract(bool force = false) override;
		std::string debugExtra() const override;

		bool maySpill() const override { return false; }
		Instruction * copy() const override;
	};
}
