#pragma once

#include "instruction/WhyInstruction.h"

namespace LL2W {
	struct Label: WhyInstruction {
		std::string name;

		Label(const std::string &name_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
		bool showDebug() const override { return false; }
		Instruction * copy() const override;
	};
}
