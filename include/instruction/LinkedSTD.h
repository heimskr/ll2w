#pragma once

#include "instruction/RType.h"

namespace LL2W {
	/** Usable only with R types. */
	template <typename T = RType>
	struct LinkedSTD: T {
		using T::T;

		bool fixSignedness() override {
			const bool one = this->rs->type->shareSignedness(this->rd->type);
			const bool two = this->rs->type->shareSignedness(this->rt->type);
			return one || two;
		}
	};
}
