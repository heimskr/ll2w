#pragma once

#include "instruction/IType.h"
#include "instruction/LinkedSD.h"

namespace LL2W {
	struct DiviIInstruction: LinkedSD<IType<>> {
		using LinkedSD::LinkedSD;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
