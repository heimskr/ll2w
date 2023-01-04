#pragma once

#include "instruction/LinkedSTD.h"
#include "instruction/RType.h"

namespace LL2W {
	/** $rs x $rt -> $rd */
	struct XorRInstruction: LinkedSTD<> {
		using LinkedSTD::LinkedSTD;
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
