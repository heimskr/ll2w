#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** %ring imm */
	struct RingIInstruction: IType {
		RingIInstruction(Immediate imm_);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
