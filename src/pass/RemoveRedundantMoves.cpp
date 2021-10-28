#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/RemoveRedundantMoves.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void removeRedundantMoves(Function &function) {
		Timer timer("RemoveRedundantMoves");
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (auto *move = dynamic_cast<MoveInstruction *>(instruction.get())) {
				if (move->rs->compareRegisters(*move->rd))
					to_remove.push_back(instruction);
			}
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);
	}
}
