#pragma once

#include "compiler/StackLocation.h"
#include "instruction/IntermediateInstruction.h"

namespace LL2W {
	class Variable;

	struct StackLoadInstruction: IntermediateInstruction {
		std::shared_ptr<Variable> result;
		StackLocation location;

		StackLoadInstruction(std::shared_ptr<Variable> result_, const StackLocation &location_, int index_):
			IntermediateInstruction(index_), result(result_), location(location_) {}

		ExtractionResult extract(bool force = false) override;
		std::string debugExtra() const override;

		bool maySpill() const override { return false; }
		Instruction * copy() const override;
	};
}
