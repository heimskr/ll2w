#pragma once

#include "instruction/IType.h"

namespace LL2W {
	struct OrIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
		static long apply(long left, long right) { return left | right; }
	};
}
