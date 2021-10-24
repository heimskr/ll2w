#pragma once

#include "instruction/IType.h"

namespace LL2W {
	struct ModuIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
