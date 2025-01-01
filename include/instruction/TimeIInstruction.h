#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** %time imm */
	struct TimeIInstruction: IType {
		TimeIInstruction(Immediate imm_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
