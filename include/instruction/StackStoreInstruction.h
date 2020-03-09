#ifndef INSTRUCTION_STACKSTOREINSTRUCTION_H_
#define INSTRUCTION_STACKSTOREINSTRUCTION_H_

#include "compiler/StackLocation.h"
#include "instruction/IntermediateInstruction.h"

namespace LL2W {
	class Variable;

	class StackStoreInstruction: public IntermediateInstruction {
		public:
			StackLocation location;
			std::shared_ptr<Variable> variable;

			StackStoreInstruction(const StackLocation &location_, std::shared_ptr<Variable> variable_, int index_ = -1):
				IntermediateInstruction(index_), location(location_), variable(variable_) {}

			std::string debugExtra() override;
	};
}

#endif
