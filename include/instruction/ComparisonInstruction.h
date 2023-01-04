#pragma once

#include "parser/Enums.h"

#include <stdexcept>

namespace LL2W {
	/** Note that Why currently has no != instruction. */
	class ComparisonInstruction {
		public:
			IcmpCond cond;

			ComparisonInstruction(IcmpCond cond_): cond(cond_) {
				if (cond_ == IcmpCond::Ne)
					throw std::invalid_argument("IcmpCond::Ne has no corresponding instruction");
			}
	};
}
