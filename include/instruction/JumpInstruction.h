#pragma once

#include "instruction/Conditional.h"
#include "instruction/JType.h"

namespace LL2W {
	struct JumpInstruction: JType<>, Conditional {
		JumpInstruction(ValueType addr_, bool link_, Condition condition_ = Condition::None, int index_ = -1);

		std::string debugExtra() const override;
		std::string toString() const override;
		bool isBlockTerminal() const override;

		/** Kind of a hack to make MinimizeBlocks work. Comes from an oversight in ll2x. */
		bool canFallThrough() const override {
			return link;
		}

		Instruction * copy() const override;
	};
}
