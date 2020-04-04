#ifndef PASS_LOWERMEMORY_H_
#define PASS_LOWERMEMORY_H_

#include <memory>

namespace LL2W {
	struct Constant;
	class Function;
	class Instruction;
	class LLVMInstruction;
}

namespace LL2W::Passes {
	/** Replaces loads and stores with Why instructions. */
	int lowerMemory(Function &);

	/** Replaces a load instruction with a Why instruction. */
	void lowerLoad(Function &, std::shared_ptr<Instruction> &, LLVMInstruction &);

	/** Replaces a store instruction with a Why instruction. */
	void lowerStore(Function &, std::shared_ptr<Instruction> &, LLVMInstruction &);

	int getLoadStoreSize(std::shared_ptr<Constant> &);
}

#endif
