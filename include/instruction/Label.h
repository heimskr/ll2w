#pragma once

#include "instruction/WhyInstruction.h"

namespace LL2W {
	struct Label: WhyInstruction {
		std::string name;

		Label(std::string name);

		std::string debugExtra() const override;
		std::string toString() const override;
		bool showDebug() const override { return false; }
		Instruction * copy() const override;
	};
}
