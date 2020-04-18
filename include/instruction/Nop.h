#ifndef INSTRUCTION_NOP_H_
#define INSTRUCTION_NOP_H_

#include "instruction/WhyInstruction.h"

namespace LL2W {
	struct Nop: public WhyInstruction {
		Nop(int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
