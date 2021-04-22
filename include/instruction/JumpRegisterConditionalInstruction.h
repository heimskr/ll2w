#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct JumpRegisterConditionalInstruction: public RType {
		bool link;

		JumpRegisterConditionalInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_,
		bool link_ = false, int index_ = -1):
			RType(rs_, nullptr, rd_, index_), link(link_) {}

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
