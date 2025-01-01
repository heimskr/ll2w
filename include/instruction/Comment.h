#pragma once

#include "instruction/WhyInstruction.h"

namespace LL2W {
	struct Comment: WhyInstruction {
		std::string text;

		Comment(std::string text);

		bool showDebug() const override { return false; }

		std::string debugExtra() const override;
		std::string toString() const override;

		Instruction * copy() const override;

		bool traditionallyIgnored() const override { return true; }
	};
}
