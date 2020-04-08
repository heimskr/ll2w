#ifndef INSTRUCTIONS_JUMPCONDITIONALINSTRUCTION_H_
#define INSTRUCTIONS_JUMPCONDITIONALINSTRUCTION_H_

#include <sstream>

#include "instruction/JType.h"

namespace LL2W {
	struct JumpConditionalInstruction: public JType<> {
		using JType::JType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
