#ifndef INSTRUCTION_COMPARISONIINSTRUCTION_H_
#define INSTRUCTION_COMPARISONIINSTRUCTION_H_

#include <unordered_map>

#include "instruction/ComparisonInstruction.h"
#include "instruction/IType.h"
#include "parser/Enums.h"

namespace LL2W {
	/**
	 * $rs == (<=, <...) $rt -> $rd (/u)
	 */
	struct ComparisonIInstruction: public IType<int>, public ComparisonInstruction {
		ComparisonIInstruction(VariablePtr rs_, int imm_, VariablePtr rd_, IcmpCond cond_, int index_ = -1):
			IType(rs_, imm_, rd_, index_), ComparisonInstruction(cond_) {}

		std::string debugExtra() override;
	};
}

#endif
