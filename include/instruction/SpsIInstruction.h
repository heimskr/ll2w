#pragma once

#include "instruction/HasSize.h"
#include "instruction/IType.h"

namespace LL2W {
	/**
	 * $rs -> [$fp - imm]
	 */
	struct SpsIInstruction: IType, HasSize {
		SpsIInstruction(Immediate imm, VariablePtr rd, WASMSize);

		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
