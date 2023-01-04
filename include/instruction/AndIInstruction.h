#pragma once

#include "instruction/IType.h"

namespace LL2W {
	struct AndIInstruction: public IType<> {
		using IType::IType;
		std::string debugExtra() override;
		std::string toString() const override;
		static int64_t apply(int64_t left, int64_t right) { return left & right; }
		void fixSignedness() override;
	};
}
