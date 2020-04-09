#ifndef INSTRUCTION_XORRINSTRUCTION_H_
#define INSTRUCTION_XORRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct XorRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
