#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/** imm >> $rs -> $rd */
	struct ShiftRightArithmeticInverseIInstruction: IType {
		using IType::IType;
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
