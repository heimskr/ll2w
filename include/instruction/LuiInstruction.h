#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** lui: imm -> $rd */
	struct LuiInstruction: IType<> {
		LuiInstruction(VariablePtr rd_, ValueType imm_, int index_ = -1):
			IType(nullptr, std::move(imm_), std::move(rd_), index_) {}
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
