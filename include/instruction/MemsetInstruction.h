#ifndef INSTRUCTION_MEMSETRINSTRUCTION_H_
#define INSTRUCTION_MEMSETRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct MemsetInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
