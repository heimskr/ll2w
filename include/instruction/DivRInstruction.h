#ifndef INSTRUCTION_DIVRINSTRUCTION_H_
#define INSTRUCTION_DIVRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct DivRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
