#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/RemoveRedundantMoves.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void removeRedundantMoves(Function &function) {
		Timer timer("RemoveRedundantMoves");
		std::vector<InstructionPtr> to_remove;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			if (auto *move = dynamic_cast<MoveInstruction *>(instruction.get())) {
				if (move->rs->compareRegisters(*move->rd)) {
					to_remove.push_back(instruction);
				}
			}
		}

		for (const InstructionPtr &instruction: to_remove) {
			function.remove(instruction);
		}
	}
}
