#pragma once

#include "parser/Enums.h"

#include <stdexcept>

namespace LL2W {
	/**
	 * Note that Why currently has no != instruction.
	 */
	class ComparisonInstruction {
		protected:
			bool isUnsigned() const;

		public:
			IcmpCond cond;

			ComparisonInstruction(IcmpCond cond): cond(cond) {
				if (cond == IcmpCond::Ne) {
					throw std::invalid_argument("IcmpCond::Ne has no corresponding instruction");
				}
			}
	};
}
