#pragma once

#include "instruction/Conditional.h"
#include "instruction/RType.h"

namespace LL2W {
	struct JumpRegisterInstruction: public RType, public Conditional {
		bool link;

		JumpRegisterInstruction(std::shared_ptr<Variable> rd_, bool link_ = false,
		Condition condition_ = Condition::None, int index_ = -1):
			RType(nullptr, nullptr, rd_, index_), Conditional(condition_), link(link_) {}

		std::string debugExtra() override;
		std::string toString() const override;
		bool alwaysTerminal() const override;
	};
}
