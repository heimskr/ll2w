#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct ModuRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() const override;
		std::string toString() const override;
		Instruction * copy() const override;
	};
}
