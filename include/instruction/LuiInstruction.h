#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * lui: imm -> $rd
	 */
	struct LuiInstruction: public IType<> {
		LuiInstruction(std::shared_ptr<Variable> rd_, ValueType imm_, int index_ = -1):
			IType(nullptr, imm_, rd_, index_) {}
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
