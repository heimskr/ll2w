#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/JumpInstruction.h"
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
				// Prevents labels from getting removed when they shouldn't be.
				// Blocks shouldn't merge after removal of an `unreachable` statement.
				auto jump = std::make_shared<JumpInstruction>(StringSet::intern("unreachable"), false);
				function.insertBefore(instruction, std::move(jump), false)->setDebug(*instruction)->extract();
			}
		}

		for (const InstructionPtr &instruction: to_remove) {
			function.remove(instruction);
		}

		return to_remove.size();
	}
}
