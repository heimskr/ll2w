#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "pass/RemoveUselessBranches.h"

namespace LL2W::Passes {
	void removeUselessBranches(Function &function) {
		std::list<InstructionPtr> to_remove;
		for (auto iter = function.blocks.begin(), end = function.blocks.end(); iter != end; ++iter) {
			BasicBlockPtr &block = *iter;
			if (block->instructions.empty())
				continue;
			InstructionPtr &back = block->instructions.back();
			if (LLVMInstruction *llback = dynamic_cast<LLVMInstruction *>(back.get())) {
				if (llback->node->nodeType() == NodeType::BrUncond) {
					if (const BrUncondNode *branch = dynamic_cast<BrUncondNode *>(llback->node)) {
						auto next = iter;
						++next;
						if (next != end) {
							const std::string destination = branch->destination->substr(1);
							if (*(*next)->label == destination)
								to_remove.push_back(back);
						}
					} else throw std::runtime_error("branch is null in Function::removeUselessBranches");
				}
			}
		}

		for (InstructionPtr &ptr: to_remove)
			function.remove(ptr);
	}
}
