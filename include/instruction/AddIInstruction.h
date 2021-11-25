#pragma once

#include "instruction/IType.h"

namespace LL2W {
	struct AddIInstruction: IType<>, Makeable<AddIInstruction> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
