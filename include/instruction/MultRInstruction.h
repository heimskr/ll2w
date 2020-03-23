#ifndef INSTRUCTION_MULTRINSTRUCTION_H_
#define INSTRUCTION_MULTRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct MultRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
	};
}

#endif
