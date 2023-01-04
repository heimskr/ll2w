#pragma once

#include <sstream>

#include "instruction/JType.h"

namespace LL2W {
	struct JumpConditionalInstruction: JType<> {
		using JType::JType;
		std::string debugExtra() const override;
		std::string toString() const override;
		bool canFallThrough() const override { return true; }
		Instruction * copy() const override;
	};
}
