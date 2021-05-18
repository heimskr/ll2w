#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackStoreInstruction.h"
#include "pass/ReplaceStoresAndLoads.h"

namespace LL2W::Passes {
	void replaceStoresAndLoads(Function &function) {
		std::list<InstructionPtr> to_remove, &linearInstructions = function.linearInstructions;
		bool any_changed;

		auto check_unique_load = [&](const InstructionPtr &check, const StackLocation &location) -> bool {
			for (InstructionPtr &instruction: linearInstructions) {
				if (instruction == check)
					continue;
				auto *load = dynamic_cast<StackLoadInstruction *>(instruction.get());
				if (load && load->location.offset == location.offset)
					return false;
			}

			return true;
		};

		do {
			any_changed = false;
			for (auto iter = linearInstructions.begin(), end = linearInstructions.end(); iter != end; ++iter) {
				InstructionPtr &start = *iter;
				auto *store = dynamic_cast<StackStoreInstruction *>(start.get());
				if (!store)
					continue;
				auto iter2 = iter;
				for (++iter2; iter2 != end; ++iter2) {
					InstructionPtr &next = *iter2;
					auto *load = dynamic_cast<StackLoadInstruction *>(next.get());
					if (!load && !dynamic_cast<StackStoreInstruction *>(next.get()))
						break;
					if (!load)
						continue;
					if (store->location.offset == load->location.offset) {
						// If this is the only load for this stack location, we can safely remove the store.
						if (check_unique_load(start, store->location))
							to_remove.push_back(start);
						to_remove.push_back(next);
						function.insertBefore(start, std::make_shared<MoveInstruction>(store->variable, load->result))
							->setDebug(store)->extract();
						any_changed = true;
						goto remove_instructions;
					}
				}
			}

			remove_instructions:
			for (InstructionPtr &instruction: to_remove)
				function.remove(instruction);
			to_remove.clear();
		} while (any_changed);
	}
}
