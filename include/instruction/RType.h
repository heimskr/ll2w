#ifndef INSTRUCTION_RTYPE_H_
#define INSTRUCTION_RTYPE_H_

#include "instruction/WhyInstruction.h"

namespace LL2W {
	struct RType: public WhyInstruction {
		using VariablePtr = std::shared_ptr<Variable>;

		VariablePtr rs, rt, rd;

		RType(VariablePtr rs_, VariablePtr rt_, VariablePtr rd_, int index_ = -1);

		ExtractionResult extract(bool force = false) override;
		bool replaceRead(VariablePtr, VariablePtr) override;
	};
}

#endif
