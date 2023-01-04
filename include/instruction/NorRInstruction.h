#pragma once

#include "instruction/LinkedSTD.h"
#include "instruction/RType.h"

namespace LL2W {
	struct NorRInstruction: LinkedSTD<> {
		using LinkedSTD::LinkedSTD;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
