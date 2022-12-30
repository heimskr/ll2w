#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * [imm] -> [$rd]
	 */
	struct LoadIndirectIInstruction: IType<> {
		LoadIndirectIInstruction(ValueType imm_, const std::shared_ptr<Variable> &rd_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
