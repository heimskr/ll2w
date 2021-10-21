#pragma once

#include "instruction/RType.h"
#include "instruction/SizedInstruction.h"

namespace LL2W {
	/**
	 * [$rs] -> [$rd]
	 */
	struct CopyRInstruction: public RType, public SizedInstruction {
		CopyRInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_, int size_ = 8, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
