#ifndef INSTRUCTION_LOADRINSTRUCTION_H_
#define INSTRUCTION_LOADRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct LoadRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
	};
}

#endif
