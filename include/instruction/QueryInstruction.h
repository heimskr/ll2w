#pragma once

#include "instruction/RType.h"
#include "parser/Enums.h"

namespace LL2W {
	/**
	 * ? type -> $rd
	 */
	struct QueryInstruction: public RType {
		QueryType type;
		QueryInstruction(QueryType type_, VariablePtr rd_, int index_ = -1):
			RType(nullptr, nullptr, rd_, index_), type(type_) {}
		std::string debugExtra() override;
		std::string toString() const override;
	};
}
