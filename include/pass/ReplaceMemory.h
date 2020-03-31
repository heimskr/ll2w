#ifndef PASS_REPLACEMEMORY_H_
#define PASS_REPLACEMEMORY_H_

#include <memory>

namespace LL2W {
	struct Constant;
	class Function;
	class Instruction;
	class LLVMInstruction;
}

namespace LL2W::Passes {
	/** Replaces loads and stores with Why instructions. */
	int replaceMemory(Function &);

	/** Replaces a load instruction with a Why instruction. */
	void replaceLoad(Function &, std::shared_ptr<Instruction> &, LLVMInstruction &);

	/** Replaces a store instruction with a Why instruction. */
	void replaceStore(Function &, std::shared_ptr<Instruction> &, LLVMInstruction &);

	int getLoadStoreSize(std::shared_ptr<Constant> &);
}

#endif
