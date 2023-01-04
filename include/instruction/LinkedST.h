#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** Usable only with R types. */
	template <typename T = RType>
	struct LinkedST: T {
		using T::T;

		bool fixSignedness() override {
			return this->rs->type->shareSignedness(this->rt->type);
		}
	};
}
