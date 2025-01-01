#pragma once

#include "instruction/Conditional.h"
#include "instruction/RType.h"

namespace LL2W {
	struct JumpRegisterInstruction: public RType, public Conditional {
		bool link;

		JumpRegisterInstruction(VariablePtr rd, bool link = false, Condition condition = Condition::None):
			RType(nullptr, nullptr, std::move(rd)),
			Conditional(condition),
			link(link) {}

		std::pair<char, char> extract(bool = false) override;
		bool replaceRead(const VariablePtr &, const VariablePtr &) override;
		bool canReplaceRead(const VariablePtr &) const override;
		bool replaceWritten(const VariablePtr &, const VariablePtr &) override;
		bool canReplaceWritten(const VariablePtr &) const override;

		std::string debugExtra() const override;
		std::string toString() const override;
		bool isBlockTerminal() const override;
		Instruction * copy() const override;
	};
}
