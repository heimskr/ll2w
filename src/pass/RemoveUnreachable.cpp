#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "pass/RemoveUnreachable.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	size_t removeUnreachable(Function &function) {
		Timer timer{"RemoveUnreachable"};
		std::vector<InstructionPtr> to_remove;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			auto *llvm = dynamic_cast<LLVMInstruction *>(instruction.get());
			if (llvm && llvm->getNodeType() == NodeType::Unreachable) {
				to_remove.emplace_back(instruction);
			}
		}

		for (InstructionPtr &instruction: to_remove) {
			function.remove(std::move(instruction));
		}

		return to_remove.size();
	}
}
