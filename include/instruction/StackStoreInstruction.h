#pragma once

#include "compiler/StackLocation.h"
#include "instruction/IntermediateInstruction.h"

namespace LL2W {
	class Variable;

	class StackStoreInstruction: public IntermediateInstruction {
		public:
			StackLocation location;
			std::shared_ptr<Variable> variable, originalVariable;

			StackStoreInstruction(const StackLocation &location_, std::shared_ptr<Variable> variable_, int index_ = -1):
				IntermediateInstruction(index_),
				location(location_), variable(variable_), originalVariable(variable_) {}

			ExtractionResult extract(bool force = false) override;
			std::string debugExtra() override;

			bool operator==(const StackStoreInstruction &) const;
	};
}
