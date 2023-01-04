#pragma once

#include "instruction/IType.h"

namespace LL2W {
	/**
	 * [imm] -> $rd
	 */
	struct LoadIInstruction: IType {
		LoadIInstruction(Immediate imm_, VariablePtr rd_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
