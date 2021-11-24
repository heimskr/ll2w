#pragma once

#include "instruction/RType.h"
#include "instruction/SizedInstruction.h"

namespace LL2W {
	/** $rs -> [$rd] */
	struct StoreRInstruction: public RType, public SizedInstruction {
		StoreRInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rt_, int size_ = 8, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
