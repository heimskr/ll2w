#ifndef PASS_LOWERMATH_H_
#define PASS_LOWERMATH_H_

#include <memory>

namespace LL2W {
	struct BasicMathNode;
	class Function;
	class Instruction;
	struct LogicNode;
}

namespace LL2W::Passes {
	using InstructionPtr = std::shared_ptr<Instruction>;

	/** Lowers mathematical and logic instructions. */
	int lowerMath(Function &);

	void lowerMath(Function &, InstructionPtr &, BasicMathNode *);
	void lowerAdd(Function &, InstructionPtr &, BasicMathNode *);
	void lowerSub(Function &, InstructionPtr &, BasicMathNode *);
	void lowerMul(Function &, InstructionPtr &, BasicMathNode *);

	void lowerLogic(Function &, InstructionPtr &, LogicNode *);
}

#endif
