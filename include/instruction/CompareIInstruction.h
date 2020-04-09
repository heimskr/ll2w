#ifndef INSTRUCTION_COMPAREIINSTRUCTION_H_
#define INSTRUCTION_COMPAREIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct CompareIInstruction: public IType<int> {
		CompareIInstruction(VariablePtr rs_, int imm_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
