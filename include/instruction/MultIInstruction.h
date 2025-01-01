#pragma once

#include "instruction/IType.h"

namespace LL2W {
	struct MultIInstruction: IType, Makeable<MultIInstruction> {
		MultIInstruction(VariablePtr rs, Immediate imm);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
