#pragma once

#include "instruction/IType.h"
#include "instruction/LinkedSD.h"

namespace LL2W {
	struct AddIInstruction: LinkedSD<IType>, Makeable<AddIInstruction> {
		using LinkedSD::LinkedSD;
		std::string debugExtra() const override;
		std::string toString() const override;
		static int64_t apply(int64_t left, int64_t right) { return left + right; }
		Instruction * copy() const override;
	};
}
