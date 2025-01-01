#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** %int imm */
	struct IntIInstruction: IType {
		IntIInstruction(Immediate imm_): IType(nullptr, imm_, nullptr) {}
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
