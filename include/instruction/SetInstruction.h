#ifndef INSTRUCTION_SETINSTRUCTION_H_
#define INSTRUCTION_SETINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct SetInstruction: public IType<int> {
		SetInstruction(std::shared_ptr<Variable> rd_, int imm_, int index_ = -1): IType(nullptr, imm_, rd_, index_) {}
		std::string debugExtra() override;
	};
}

#endif
