#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** %int imm */
	struct IntIInstruction: IType {
		IntIInstruction(Immediate imm_, int index_ = -1): IType(nullptr, imm_, nullptr, index_) {}
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
