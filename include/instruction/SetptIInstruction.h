#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * setpt imm
	 */
	struct SetptIInstruction: public IType<> {
		SetptIInstruction(ValueType imm_, int index_ = -1): IType(nullptr, imm_, nullptr, index_) {}
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
