#pragma once

#include "instruction/IType.h"

namespace LL2W {
	struct MultIInstruction: IType<>, Makeable<MultIInstruction> {
		MultIInstruction(std::shared_ptr<Variable> rs_, ValueType imm_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
