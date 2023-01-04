#pragma once

#include "instruction/RType.h"

namespace LL2W {
	struct ThreeSourcesRType: RType {
		using RType::RType;
		std::pair<char, char> extract(bool = false) override;
		bool replaceRead(const VariablePtr &, const VariablePtr &) override;
		bool canReplaceRead(const VariablePtr &) const override;
		bool replaceWritten(const VariablePtr &, const VariablePtr &) override;
		bool canReplaceWritten(const VariablePtr &) const override;
	};
}
