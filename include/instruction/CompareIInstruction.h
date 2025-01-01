#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** $rs ~ imm */
	struct CompareIInstruction: IType {
		CompareIInstruction(VariablePtr rs, Immediate imm);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
