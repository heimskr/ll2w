#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackStoreInstruction.h"
#include "pass/ReplaceStoresAndLoads.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void replaceStoresAndLoads(Function &function) {
		Timer timer{"ReplaceStoresAndLoads"};
		std::list<InstructionPtr> to_remove;
		bool any_changed{};

		auto check_unique_load = [&](const InstructionPtr &check, const StackLocation &location) -> bool {
			for (InstructionPtr &instruction: function.linearInstructions) {
				if (instruction == check) {
					continue;
				}

				auto *load = dynamic_cast<StackLoadInstruction *>(instruction.get());
				if (load && load->location.offset == location.offset) {
					return false;
				}
			}

			return true;
		};

		do {
			any_changed = false;
			for (auto iter = function.linearInstructions.begin(), end = function.linearInstructions.end(); iter != end; ++iter) {
				const InstructionPtr &start = *iter;

				auto *store = dynamic_cast<StackStoreInstruction *>(start.get());
				if (!store) {
					continue;
				}

				auto iter2 = iter;
				for (++iter2; iter2 != end; ++iter2) {
					const InstructionPtr &next = *iter2;
					auto *load = dynamic_cast<StackLoadInstruction *>(next.get());

					if (!load) {
						if (!dynamic_cast<StackStoreInstruction *>(next.get())) {
							break;
						}
						continue;
					}

					if (store->location.offset == load->location.offset) {
						// If this is the only load for this stack location, we can safely remove the store.
						if (check_unique_load(start, store->location)) {
							to_remove.push_back(start);
						}
						to_remove.push_back(next);
						function.insertBefore(start, std::make_shared<MoveInstruction>(store->variable, load->result))->setDebug(store)->extract();
						any_changed = true;
						goto remove_instructions;
					}
				}
			}

			remove_instructions:
			for (const InstructionPtr &instruction: to_remove) {
				function.remove(instruction);
			}

			to_remove.clear();
		} while (any_changed);
	}
}
