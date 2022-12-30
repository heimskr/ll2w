#include "compiler/Function.h"
#include "instruction/AddIInstruction.h"
#include "instruction/DeferredDestinationMoveInstruction.h"
#include "instruction/DeferredSourceMoveInstruction.h"
#include "instruction/LoadRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "pass/FinishMultireg.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void finishMultireg(Function &function) {
		Timer timer("FinishMultireg");
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (auto *defsource = dynamic_cast<DeferredSourceMoveInstruction *>(instruction.get())) {
				if (defsource->rs->registers.empty())
					throw std::runtime_error("Deferred-source move has no registers allocated to rs");
				int reg = *std::next(defsource->rs->registers.begin(), defsource->registerIndex);
				auto var = function.makePrecoloredVariable(reg, defsource->parent.lock());
				auto move = std::make_shared<MoveInstruction>(var, defsource->rd);
				function.insertBefore(instruction, move)->setDebug(defsource)->extract();
				to_remove.push_back(instruction);
			} else if (auto *defdest = dynamic_cast<DeferredDestinationMoveInstruction *>(instruction.get())) {
				if (defdest->rd->registers.empty())
					throw std::runtime_error("Deferred-destination move has no registers allocated to rd");
				int reg = *std::next(defdest->rd->registers.begin(), defdest->registerIndex);
				auto var = function.makePrecoloredVariable(reg, defdest->parent.lock());
				auto move = std::make_shared<MoveInstruction>(defdest->rs, var);
				function.insertBefore(instruction, move)->setDebug(defdest)->extract();
				to_remove.push_back(instruction);
			} else if (auto *load = dynamic_cast<LoadRInstruction *>(instruction.get())) {
				if (load->rd->registers.size() < 2)
					continue;

				auto m4 = function.mx(4, instruction);
				auto move = std::make_shared<MoveInstruction>(load->rs, m4);
				function.insertBefore(instruction, move)->setDebug(load)->extract();
				auto iter = load->rd->registers.begin();
				auto bytes_remaining = load->rd->type->width() / 8;

				while (8 <= bytes_remaining) {
					auto precolored = function.makePrecoloredVariable(*iter++, load->parent.lock());
					auto new_load = std::make_shared<LoadRInstruction>(m4, precolored, 8);
					function.insertBefore(instruction, new_load)->setDebug(load)->extract();
					bytes_remaining -= 8;
					if (0 < bytes_remaining)
						function.insertBefore(instruction, std::make_shared<AddIInstruction>(m4, 8, m4))
							->setDebug(load)->extract();
				}

				for (int size = 4; 0 < size; size /= 2) {
					if (size <= bytes_remaining) {
						auto precolored = function.makePrecoloredVariable(*iter++, load->parent.lock());
						auto new_load = std::make_shared<LoadRInstruction>(m4, precolored, size);
						function.insertBefore(instruction, new_load)->setDebug(load)->extract();
						bytes_remaining -= size;
						if (0 < bytes_remaining)
							function.insertBefore(instruction, std::make_shared<AddIInstruction>(m4, size, m4))
								->setDebug(load)->extract();
					}
				}

				to_remove.push_back(instruction);
			} else if (auto *store = dynamic_cast<StoreRInstruction *>(instruction.get())) {
				if (store->rs->registers.size() < 2)
					continue;
				auto m4 = function.mx(4, instruction);
				auto move = std::make_shared<MoveInstruction>(store->rt, m4);
				function.insertBefore(instruction, move)->setDebug(store)->extract();
				auto iter = store->rs->registers.begin();
				auto bytes_remaining = store->rs->type->width() / 8;
				while (8 <= bytes_remaining) {
					auto precolored = function.makePrecoloredVariable(*iter++, store->parent.lock());
					auto new_store = std::make_shared<StoreRInstruction>(precolored, m4, 8);
					function.insertBefore(instruction, new_store)->setDebug(store)->extract();
					bytes_remaining -= 8;
					if (0 < bytes_remaining)
						function.insertBefore(instruction, std::make_shared<AddIInstruction>(m4, 8, m4))
							->setDebug(store)->extract();
				}
				for (int size = 4; 0 < size; size /= 2) {
					if (size <= bytes_remaining) {
						auto precolored = function.makePrecoloredVariable(*iter++, store->parent.lock());
						auto new_store = std::make_shared<StoreRInstruction>(precolored, m4, size);
						function.insertBefore(instruction, new_store)->setDebug(store)->extract();
						bytes_remaining -= size;
						if (0 < bytes_remaining)
							function.insertBefore(instruction, std::make_shared<AddIInstruction>(m4, size, m4))
								->setDebug(store)->extract();
					}
				}
				to_remove.push_back(instruction);
			}
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);
	}
}
