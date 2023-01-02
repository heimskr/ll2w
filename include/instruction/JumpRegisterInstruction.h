#pragma once

#include "instruction/Conditional.h"
#include "instruction/RType.h"

namespace LL2W {
	struct JumpRegisterInstruction: public RType, public Conditional {
		bool link;

		JumpRegisterInstruction(VariablePtr rd_, bool link_ = false,
		Condition condition_ = Condition::None, int index_ = -1):
			RType(nullptr, nullptr, std::move(rd_), index_), Conditional(condition_), link(link_) {}

		std::pair<char, char> extract(bool = false) override;
		bool replaceRead(const VariablePtr &, const VariablePtr &) override;
		bool canReplaceRead(const VariablePtr &) const override;
		bool replaceWritten(const VariablePtr &, const VariablePtr &) override;
		bool canReplaceWritten(const VariablePtr &) const override;

		std::string debugExtra() override;
		std::string toString() const override;
		bool alwaysTerminal() const override;
	};
}
