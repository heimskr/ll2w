#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * rit imm
	 */
	struct RitIInstruction: public IType<> {
		RitIInstruction(ValueType imm_, int index_ = -1): IType(nullptr, imm_, nullptr, index_) {}
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
