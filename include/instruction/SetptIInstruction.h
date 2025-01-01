#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** setpt imm */
	struct SetptIInstruction: IType {
		SetptIInstruction(Immediate imm_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
