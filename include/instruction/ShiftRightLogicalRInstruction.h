#ifndef INSTRUCTION_SHIFTRIGHTLOGICALRINSTRUCTION_H_
#define INSTRUCTION_SHIFTRIGHTLOGICALRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct ShiftRightLogicalRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
