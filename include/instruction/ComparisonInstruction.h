#ifndef INSTRUCTION_COMPARISONINSTRUCTION_H_
#define INSTRUCTION_COMPARISONINSTRUCTION_H_

#include <stdexcept>

#include "parser/Enums.h"

namespace LL2W {
	/**
	 * Note that Why currently has no != instruction.
	 */
	class ComparisonInstruction {
		protected:
			bool isUnsigned() const;

		public:
			IcmpCond cond;

			ComparisonInstruction(IcmpCond cond_): cond(cond_) {
				if (cond_ == IcmpCond::Ne)
					throw std::invalid_argument("IcmpCond::Ne has no corresponding instruction");
			}
	};
}

#endif
