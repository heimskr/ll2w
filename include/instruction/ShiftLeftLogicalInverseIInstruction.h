#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** imm << $rs -> $rd */
	struct ShiftLeftLogicalInverseIInstruction: IType<> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
