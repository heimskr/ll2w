#ifndef INSTRUCTION_COMPARISONRINSTRUCTION_H_
#define INSTRUCTION_COMPARISONRINSTRUCTION_H_

#include <unordered_map>

#include "instruction/ComparisonInstruction.h"
#include "instruction/RType.h"
#include "parser/Enums.h"

namespace LL2W {
	/**
	 * $rs == (<=, <...) $rt -> $rd (/u)
	 */
	struct ComparisonRInstruction: public RType, public ComparisonInstruction {
		ComparisonRInstruction(VariablePtr rs_, VariablePtr rt_, VariablePtr rd_, IcmpCond cond_, int index_ = -1):
			RType(rs_, rt_, rd_, index_), ComparisonInstruction(cond_) {}

		std::string debugExtra() override;
	};
}

#endif
