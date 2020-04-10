#ifndef INSTRUCTION_SHIFTRIGHTARITHMETICIINSTRUCTION_H_
#define INSTRUCTION_SHIFTRIGHTARITHMETICIINSTRUCTION_H_

#include "instruction/IType.h"

namespace LL2W {
	struct ShiftRightArithmeticIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
