#pragma once

#include "compiler/StackLocation.h"
#include "instruction/IntermediateInstruction.h"

namespace LL2W {
	class Variable;

	struct StackStoreInstruction: IntermediateInstruction {
		StackLocation location;
		std::shared_ptr<Variable> variable;
		std::shared_ptr<Variable> originalVariable;

		StackStoreInstruction(StackLocation location_, std::shared_ptr<Variable> variable_):
			IntermediateInstruction(index_),
			location(std::move(location_)),
			variable(variable_),
			originalVariable(std::move(variable_)) {}

		ExtractionResult extract(bool force = false) override;
		std::string debugExtra() const override;

		bool operator==(const StackStoreInstruction &) const;
		Instruction * copy() const override;
	};
}
