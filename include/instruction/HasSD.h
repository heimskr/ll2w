#pragma once

#include "parser/Enums.h"

#include <memory>

namespace LL2W {
	class Variable;

	using VariablePtr = std::shared_ptr<Variable>;

	template <typename T>
	struct HasSD: T {
		using SDPointer = VariablePtr HasSD::*;

		template <typename... Args>
		HasSD(VariablePtr rs_, VariablePtr rd_, Args &&...args):
			T(args...), rs(std::move(rs_)), rd(std::move(rd_)) {}

		VariablePtr rs;
		VariablePtr rd;

		virtual Role rsRole() const { return Role::Source; }
		virtual Role rdRole() const { return Role::Destination; }
	};
}
