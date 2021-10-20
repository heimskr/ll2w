#include "compiler/Function.h"
#include "instruction/AddIInstruction.h"
#include "instruction/DeferredDestinationMoveInstruction.h"
#include "instruction/DeferredSourceMoveInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/MoveInstruction.h"

#include "pass/FinishMultireg.h"

namespace LL2W::Passes {
	void finishMultireg(Function &function) {
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (auto *defsource = dynamic_cast<DeferredSourceMoveInstruction *>(instruction.get())) {
				if (defsource->rs->registers.empty())
					throw std::runtime_error("Deferred-source move has no registers allocated to rs");
				int reg = *std::next(defsource->rs->registers.begin(), defsource->registerIndex);
				auto var = function.makePrecoloredVariable(reg, defsource->parent.lock());
				auto move = std::make_shared<MoveInstruction>(var, defsource->rd);
				move->setDebug(defsource->debugIndex);
				function.insertBefore(instruction, move);
				to_remove.push_back(instruction);
			} else if (auto *defdest = dynamic_cast<DeferredDestinationMoveInstruction *>(instruction.get())) {
				if (defdest->rd->registers.empty())
					throw std::runtime_error("Deferred-destination move has no registers allocated to rd");
				int reg = *std::next(defdest->rd->registers.begin(), defdest->registerIndex);
				auto var = function.makePrecoloredVariable(reg, defdest->parent.lock());
				auto move = std::make_shared<MoveInstruction>(defdest->rs, var);
				move->setDebug(defdest->debugIndex);
				function.insertBefore(instruction, move);
				to_remove.push_back(instruction);
			} else if (auto *load = dynamic_cast<LoadRInstruction *>(instruction.get())) {
				if (load->rd->registers.size() < 2)
					continue;
				if (load->size % 8)
					throw std::runtime_error("Load into register pack has a size that isn't divisible by 8");
				auto m4 = function.mx(4, instruction);
				auto move = std::make_shared<MoveInstruction>(load->rs, m4);
				move->setDebug(load->debugIndex);
				function.insertBefore(instruction, move);
				move->extract();
				auto iter = load->rd->registers.begin();
				for (int i = 0; i < load->size / 8; ++i) {
					if (i != 0)
						function.insertBefore(instruction, std::make_shared<AddIInstruction>(m4, 8, m4))
							->setDebug(load->debugIndex)->extract();
					auto precolored = function.makePrecoloredVariable(*iter++, load->parent.lock());
					auto new_load = std::make_shared<LoadRInstruction>(m4, precolored, 8);
					new_load->setDebug(load->debugIndex);
					function.insertBefore(instruction, new_load);
					new_load->extract();
				}
				to_remove.push_back(instruction);
			}
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);
	}
}
