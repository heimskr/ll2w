#pragma once

#include "instruction/IType.h"
#include "util/Makeable.h"

namespace LL2W {
	/** imm -> $rd */
	struct SetInstruction: IType, Makeable<SetInstruction> {
		SetInstruction(VariablePtr rd, Immediate imm):
			IType(nullptr, std::move(imm), std::move(rd)) {}
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
