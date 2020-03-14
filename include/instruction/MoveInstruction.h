#ifndef INSTRUCTION_MOVEINSTRUCTION_H_
#define INSTRUCTION_MOVEINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct MoveInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
	};
}

#endif
