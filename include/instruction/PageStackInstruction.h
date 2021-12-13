#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct PageStackInstruction: public RType {
		bool isPush;
		PageStackInstruction(bool is_push, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
