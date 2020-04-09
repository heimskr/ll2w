#ifndef INSTRUCTION_COMPARERINSTRUCTION_H_
#define INSTRUCTION_COMPARERINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct CompareRInstruction: public RType {
		CompareRInstruction(VariablePtr rs_, VariablePtr rt_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
