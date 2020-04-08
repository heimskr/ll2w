#ifndef INSTRUCTION_STACKPOPINSTRUCTION_H_
#define INSTRUCTION_STACKPOPINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct StackPopInstruction: public RType {
		StackPopInstruction(std::shared_ptr<Variable> rd_, int index_ = -1);
		std::string debugExtra() override;
	};
}

#endif
