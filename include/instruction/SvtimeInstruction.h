#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct SvtimeInstruction: public RType {
		SvtimeInstruction(std::shared_ptr<Variable> rd_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
