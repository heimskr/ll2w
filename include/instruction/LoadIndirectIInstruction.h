#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** [imm] -> [$rd] */
	struct LoadIndirectIInstruction: IType {
		LoadIndirectIInstruction(Immediate imm_, VariablePtr rd_, int index_ = -1);

		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
