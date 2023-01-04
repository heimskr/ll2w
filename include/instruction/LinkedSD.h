#pragma once

namespace LL2W {
	template <typename T>
	struct LinkedSD: T {
		using T::T;

		bool fixSignedness() override {
			return this->rs->type->shareSignedness(this->rd->type);
		}
	};
}
