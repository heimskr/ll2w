#ifndef INSTRUCTION_SUBRINSTRUCTION_H_
#define INSTRUCTION_SUBRINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct SubRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
	};
}

#endif
