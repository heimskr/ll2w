#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** ring imm */
	struct RingIInstruction: public IType<> {
		RingIInstruction(ValueType imm_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
