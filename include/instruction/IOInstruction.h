#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct IOInstruction: public RType {
		const std::string *ident = nullptr;

		IOInstruction(const std::string *ident_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
