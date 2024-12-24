#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "pass/RemoveUselessBranches.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void removeUselessBranches(Function &function) {
		Timer timer("RemoveUselessBranches");
		std::list<InstructionPtr> to_remove;
		for (auto iter = function.blocks.begin(), end = function.blocks.end(); iter != end; ++iter) {
			BasicBlockPtr &block = *iter;
			if (block->instructions.empty()) {
				continue;
			}

			const InstructionPtr &back = block->instructions.back();

			if (LLVMInstruction *llback = dynamic_cast<LLVMInstruction *>(back.get())) {
				if (llback->getNodeType() == NodeType::BrUncond) {
					if (const BrUncondNode *branch = dynamic_cast<BrUncondNode *>(llback->getNode())) {
						auto next = iter;
						++next;
						if (next != end) {
							const std::string destination = branch->destination->substr(1);
							if (*(*next)->getLabel() == destination) {
								to_remove.push_back(back);
							}
						}
					} else {
						throw std::runtime_error("branch is null in Function::removeUselessBranches");
					}
				}
			}
		}

		for (InstructionPtr &ptr: to_remove)
			function.remove(ptr);
	}
}
