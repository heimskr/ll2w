#ifndef INSTRUCTION_DIVURINSTRUCTION_H_
#define INSTRUCTION_DIVURINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct DivuRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() const override;
		std::string toString() const override;
	};
}

#endif
