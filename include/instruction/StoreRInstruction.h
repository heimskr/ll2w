#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** $rs -> [$rt] */
	struct StoreRInstruction: RType {
		StoreRInstruction(const std::shared_ptr<Variable> &rs_, const std::shared_ptr<Variable> &rt_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
