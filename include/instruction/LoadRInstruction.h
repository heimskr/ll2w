#pragma once

#include "instruction/LinkedSD.h"
#include "instruction/RType.h"

namespace LL2W {
	/** [$rs] -> $rd */
	struct LoadRInstruction: LinkedSD<RType> {
		LoadRInstruction(const std::shared_ptr<Variable> &rs_, const std::shared_ptr<Variable> &rd_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
