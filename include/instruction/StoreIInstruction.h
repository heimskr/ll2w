#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** $rs -> [imm] */
	struct StoreIInstruction: public IType<> {
		StoreIInstruction(const std::shared_ptr<Variable> &rs_, ValueType imm_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
