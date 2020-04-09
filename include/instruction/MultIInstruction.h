#ifndef INSTRUCTION_MULTIINSTRUCTION_H_
#define INSTRUCTION_MULTIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct MultIInstruction: public IType<int> {
		MultIInstruction(std::shared_ptr<Variable> rs_, int imm_, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
