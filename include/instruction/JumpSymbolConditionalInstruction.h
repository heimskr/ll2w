#ifndef INSTRUCTIONS_JUMPSYMBOLCONDITIONALINSTRUCTION_H_
#define INSTRUCTIONS_JUMPSYMBOLCONDITIONALINSTRUCTION_H_

#include <sstream>

#include "instruction/JType.h"

namespace LL2W {
	struct JumpSymbolConditionalInstruction: public JType<std::string> {
		using JType::JType;
		std::string debugExtra() override;
	};
}

#endif
