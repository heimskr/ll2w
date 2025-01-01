#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** lui: imm -> $rd */
	struct LuiInstruction: IType {
		LuiInstruction(VariablePtr rd, Immediate imm):
			IType(nullptr, std::move(imm), std::move(rd)) {}
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
