#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/**
	 * page -> $rd
	 */
	struct SvpgInstruction: public RType {
		SvpgInstruction(VariablePtr rd_, int index_ = -1): RType(nullptr, nullptr, rd_, index_) {}
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
