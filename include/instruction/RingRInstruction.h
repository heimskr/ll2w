#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct RingRInstruction: public RType {
		RingRInstruction(std::shared_ptr<Variable> rs_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
