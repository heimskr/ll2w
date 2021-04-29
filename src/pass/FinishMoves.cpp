#include "compiler/Function.h"
#include "instruction/DeferredDestinationMoveInstruction.h"
#include "instruction/DeferredSourceMoveInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/FinishMoves.h"

namespace LL2W::Passes {
	void finishMoves(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (auto *defsource = dynamic_cast<DeferredSourceMoveInstruction *>(instruction.get())) {
				if (defsource->rs->registers.empty())
					throw std::runtime_error("Deferred-source move has no registers allocated to rs");
				int reg = *std::next(defsource->rs->registers.begin(), defsource->registerIndex);
				auto var = function.makePrecoloredVariable(reg, defsource->parent.lock());
				auto move = std::make_shared<MoveInstruction>(var, defsource->rd);
				function.insertBefore(instruction, move);
				to_remove.push_back(instruction);
			} else if (auto *defdest = dynamic_cast<DeferredDestinationMoveInstruction *>(instruction.get())) {
				if (defdest->rd->registers.empty())
					throw std::runtime_error("Deferred-destination move has no registers allocated to rd");
				int reg = *std::next(defdest->rd->registers.begin(), defdest->registerIndex);
				auto var = function.makePrecoloredVariable(reg, defdest->parent.lock());
				auto move = std::make_shared<MoveInstruction>(defdest->rs, var);
				function.insertBefore(instruction, move);
				to_remove.push_back(instruction);
			}
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);
	}
}
