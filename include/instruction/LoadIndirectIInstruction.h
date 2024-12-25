#pragma once

#include "instruction/HasSize.h"
#include "instruction/IType.h"

namespace LL2W {
	/** [imm] -> [$rd] */
	struct LoadIndirectIInstruction: IType, HasSize {
		LoadIndirectIInstruction(Immediate imm, VariablePtr rd, WASMSize);

		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
