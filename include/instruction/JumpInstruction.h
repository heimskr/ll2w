#ifndef INSTRUCTIONS_JUMPINSTRUCTION_H_
#define INSTRUCTIONS_JUMPINSTRUCTION_H_

#include "instruction/JType.h"

namespace LL2W {
	struct JumpInstruction: public JType<int> {
		using JType::JType;

		std::string debugExtra() override;
	};
}

#endif
