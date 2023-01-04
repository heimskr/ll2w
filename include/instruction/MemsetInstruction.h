#pragma once

#include "instruction/ThreeSourcesRType.h"

namespace LL2W {
	struct MemsetInstruction: public ThreeSourcesRType {
		using ThreeSourcesRType::ThreeSourcesRType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
