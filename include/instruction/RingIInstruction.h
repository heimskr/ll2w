#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * ring imm
	 */
	struct RingIInstruction: public IType<> {
		RingIInstruction(ValueType imm_, int index_ = -1): IType(nullptr, imm_, nullptr, index_) {}
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
