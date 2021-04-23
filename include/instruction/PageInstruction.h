#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct PageInstruction: public RType {
		bool on;

		PageInstruction(bool, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
