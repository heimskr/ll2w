#pragma once

#include <memory>

namespace LL2W {
	struct BasicMathNode;
	class Function;
	class Instruction;
	struct LogicNode;
}

namespace LL2W::Passes {
	/** Lowers mathematical and logic instructions. */
	int lowerMath(Function &);

	void lowerMath(Function &, const std::shared_ptr<Instruction> &, BasicMathNode *);
	void lowerMult(Function &, const std::shared_ptr<Instruction> &, BasicMathNode *);
	void lowerSub(Function &, const std::shared_ptr<Instruction> &, BasicMathNode *);
	void lowerLogic(Function &, const std::shared_ptr<Instruction> &, LogicNode *);
}
