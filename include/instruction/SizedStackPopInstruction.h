#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct SizedStackPopInstruction: RType {
		int size = -1; // in bytes
		SizedStackPopInstruction(VariablePtr rd, int size);
		SizedStackPopInstruction(VariablePtr rd);
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
