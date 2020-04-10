#ifndef INSTRUCTION_SHIFTRIGHTARITHMETICRINSTRUCTION_H_
#define INSTRUCTION_SHIFTRIGHTARITHMETICRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct ShiftRightArithmeticRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
