#pragma once

#include "instruction/HasSize.h"
#include "instruction/IType.h"

namespace LL2W {
	/**
	 * [$fp - imm] -> $rd
	 */
	struct SplIInstruction: IType {
		SplIInstruction(Immediate imm, VariablePtr rd);

		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
