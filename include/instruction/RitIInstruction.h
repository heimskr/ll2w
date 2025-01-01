#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** %rit imm */
	struct RitIInstruction: IType {
		RitIInstruction(Immediate imm_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
