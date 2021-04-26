#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/**
	 * setpt $rs
	 */
	struct SetptRInstruction: public RType {
		SetptRInstruction(VariablePtr rs_, int index_ = -1): RType(rs_, nullptr, nullptr, index_) {}
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
