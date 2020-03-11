#ifndef INSTRUCTION_RTYPE_H_
#define INSTRUCTION_RTYPE_H_

#include "instruction/WhyInstruction.h"

namespace LL2W {
	struct RType: public WhyInstruction {
		std::shared_ptr<Variable> rs, rt, rd;

		RType(std::shared_ptr<Variable> rs_, std::shared_ptr<Variable> rt_, std::shared_ptr<Variable> rd_,
			int index_ = -1);

		ExtractionResult extract(bool force = false) override;
	};
}

#endif
