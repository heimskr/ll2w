#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct HaltInstruction: public RType {
		HaltInstruction(int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
