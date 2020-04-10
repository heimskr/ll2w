#ifndef INSTRUCTION_SHIFTLEFTLOGICALRINSTRUCTION_H_
#define INSTRUCTION_SHIFTLEFTLOGICALRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct ShiftLeftLogicalRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
