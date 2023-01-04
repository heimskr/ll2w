#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** rit imm */
	struct RitIInstruction: IType<> {
		RitIInstruction(ValueType imm_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
