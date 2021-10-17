#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct RestInstruction: public RType {
		RestInstruction(int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
