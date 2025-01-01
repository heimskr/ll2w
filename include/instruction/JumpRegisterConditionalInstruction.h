#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct JumpRegisterConditionalInstruction: public RType {
		bool link;

		JumpRegisterConditionalInstruction() = delete;

		JumpRegisterConditionalInstruction(VariablePtr rs_, VariablePtr rd_,
		bool link_ = false):
			RType(std::move(rs_), nullptr, std::move(rd_), index_), link(link_) {}

		std::pair<char, char> extract(bool = false) override;
		bool replaceRead(const VariablePtr &, const VariablePtr &) override;
		bool canReplaceRead(const VariablePtr &) const override;
		bool replaceWritten(const VariablePtr &, const VariablePtr &) override;
		bool canReplaceWritten(const VariablePtr &) const override;

		std::string debugExtra() const override;
		std::string toString() const override;

		bool canFallThrough() const override { return true; }
		Instruction * copy() const override;
	};
}
