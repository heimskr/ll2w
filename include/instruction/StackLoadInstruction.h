#pragma once

#include "compiler/StackLocation.h"
#include "instruction/IntermediateInstruction.h"

namespace LL2W {
	class Variable;

	struct StackLoadInstruction: IntermediateInstruction {
		std::shared_ptr<Variable> result;
		StackLocation location;

		StackLoadInstruction(std::shared_ptr<Variable> result_, StackLocation location_, int index_ = -1):
			IntermediateInstruction(index_), result(std::move(result_)), location(std::move(location_)) {}

		ExtractionResult extract(bool force = false) override;
		std::string debugExtra() const override;

		bool maySpill() const override { return false; }
		Instruction * copy() const override;
	};
}
