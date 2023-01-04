#pragma once

#include "instruction/IType.h"
#include "util/Makeable.h"

namespace LL2W {
	/** imm -> $rd */
	struct SetInstruction: IType, Makeable<SetInstruction> {
		SetInstruction(std::shared_ptr<Variable> rd_, Immediate imm_, int index_ = -1):
			IType(nullptr, imm_, rd_, index_) {}
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
