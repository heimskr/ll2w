#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct LogicalOrRInstruction: public RType {
		using RType::RType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
