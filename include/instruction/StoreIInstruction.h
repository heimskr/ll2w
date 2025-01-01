#pragma once

#include "instruction/HasSize.h"
#include "instruction/IType.h"
#include "instruction/SizedInstruction.h"

namespace LL2W {
	/** $rs -> [imm] */
	struct StoreIInstruction: IType, HasSize {
		StoreIInstruction(VariablePtr rs, Immediate imm, WASMSize);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
