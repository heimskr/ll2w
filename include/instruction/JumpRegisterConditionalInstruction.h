#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct JumpRegisterConditionalInstruction: public RType {
		bool link;

		JumpRegisterConditionalInstruction() = delete;

		JumpRegisterConditionalInstruction(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rd_,
		bool link_ = false, int index_ = -1):
			RType(rs_, nullptr, rd_, index_), link(link_) {}

		std::pair<char, char> extract(bool = false) override;
		bool replaceRead(VariablePtr, VariablePtr) override;
		bool canReplaceRead(VariablePtr) const override;
		bool replaceWritten(VariablePtr, VariablePtr) override;
		bool canReplaceWritten(VariablePtr) const override;

		std::string debugExtra() override;
		std::string toString() const override;
	};
}
