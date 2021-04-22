#ifndef INSTRUCTIONS_JUMPINSTRUCTION_H_
#define INSTRUCTIONS_JUMPINSTRUCTION_H_

#include "instruction/Conditional.h"
#include "instruction/JType.h"

namespace LL2W {
	struct JumpInstruction: public JType<>, public Conditional {
		JumpInstruction(ValueType addr_, bool link_, Condition condition_ = Condition::None, int index_ = -1);

		std::string debugExtra() override;
		std::string toString() const override;
	};
}

#endif
