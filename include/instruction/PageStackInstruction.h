#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct PageStackInstruction: RType {
		bool isPush;
		PageStackInstruction(bool is_push, VariablePtr rs_ = nullptr);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
