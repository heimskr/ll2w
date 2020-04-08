#ifndef INSTRUCTION_ANDRINSTRUCTION_H_
#define INSTRUCTION_ANDRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct AndRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
