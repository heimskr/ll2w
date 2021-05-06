#pragma once

#include "instruction/IType.h"

namespace LL2W {
	struct PrintPseudoinstruction: public IType<> {
		PrintPseudoinstruction(ValueType imm_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}