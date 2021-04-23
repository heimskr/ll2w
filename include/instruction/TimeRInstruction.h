#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct TimeRInstruction: public RType {
		TimeRInstruction(std::shared_ptr<Variable> rs_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
