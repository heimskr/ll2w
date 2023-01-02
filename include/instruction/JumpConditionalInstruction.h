#pragma once

#include <sstream>

#include "instruction/JType.h"

namespace LL2W {
	struct JumpConditionalInstruction: public JType<> {
		using JType::JType;
		std::string debugExtra() override;
		std::string toString() const override;
		bool canFallThrough() const override { return true; }
	};
}
