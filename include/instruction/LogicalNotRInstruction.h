#ifndef INSTRUCTION_LOGICALNOTRINSTRUCTION_H_
#define INSTRUCTION_LOGICALNOTRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct LogicalNotRInstruction: public RType {
		LogicalNotRInstruction(VariablePtr rs_, VariablePtr rd_, int index_ = -1):
			RType(rs_, nullptr, rd_, index_) {}

		LogicalNotRInstruction(VariablePtr rs_, int index_ = -1):
			RType(rs_, nullptr, rs_, index_) {}

		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
