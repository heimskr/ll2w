#pragma once

#include "instruction/IType.h"
#include "instruction/LinkedSD.h"

namespace LL2W {
	/** $rs % $rt -> $rd */
	struct ModIInstruction: LinkedSD<IType> {
		using LinkedSD::LinkedSD;
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
