#pragma once

#include "instruction/IType.h"
#include "instruction/LinkedSD.h"

namespace LL2W {
	/** $rs x imm -> $rd */
	struct XorIInstruction: LinkedSD<IType> {
		using LinkedSD::LinkedSD;
		std::string debugExtra() override;
		std::string toString() const override;
		static long apply(long left, long right) { return left ^ right; }
		Instruction * copy() const override;
	};
}
