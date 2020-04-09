#ifndef INSTRUCTION_STACKPUSHINSTRUCTION_H_
#define INSTRUCTION_STACKPUSHINSTRUCTION_H_

#include "instruction/RType.h"

namespace LL2W {
	struct StackPushInstruction: public RType {
		StackPushInstruction(std::shared_ptr<Variable> rs_, int index_ = -1);
		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
