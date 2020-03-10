#ifndef INSTRUCTION_STACKLOADINSTRUCTION_H_
#define INSTRUCTION_STACKLOADINSTRUCTION_H_

#include "compiler/StackLocation.h"
#include "instruction/IntermediateInstruction.h"

namespace LL2W {
	class Variable;

	class StackLoadInstruction: public IntermediateInstruction {
		public:
			std::shared_ptr<Variable> result;
			StackLocation location;

			StackLoadInstruction(std::shared_ptr<Variable> result_, const StackLocation &location_, int index_):
				IntermediateInstruction(index_), result(result_), location(location_) {}

			ExtractionResult extract(bool force = false) override;
			std::string debugExtra() override;

			bool maySpill() const override { return false; }
	};
}

#endif
