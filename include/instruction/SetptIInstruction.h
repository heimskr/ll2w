#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** setpt imm */
	struct SetptIInstruction: IType<> {
		SetptIInstruction(ValueType imm_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
