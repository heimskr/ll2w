#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/WhyInfo.h"
#include "instruction/AddIInstruction.h"
#include "instruction/MoveInstruction.h"
#include "instruction/StoreRInstruction.h"
#include "pass/SplitLargeMemory.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	size_t splitLargeMemory(Function &function) {
		Timer timer("SplitLargeMemory");
		size_t changed = 0;

		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions) {
			if (auto store = std::dynamic_pointer_cast<StoreRInstruction>(instruction)) {
				if (store->size <= 8)
					continue;
				if (store->size % 8 != 0) {
					warn() << "Skipping large memory operation with an unhandled size (" << store->size << "): "
					       << instruction->debugExtra() << '\n';
					continue;
				}
				const size_t register_count = store->rs->registers.size();
				const size_t expected = 8 * register_count;
				if (size_t(store->size) != expected) {
					warn() << "Expected a store size of " << expected << " for a set of " << register_count
					       << " register" << (register_count == 1? "" : "s") << ": " << instruction->debugExtra()
					       << '\n';
					continue;
				}
				auto m3 = function.mx(3, instruction);
				function.insertBefore(instruction, std::make_shared<MoveInstruction>(store->rt, m3), "SplitLargeMemory:"
					" " + store->rt->plainString() + " -> $m3")->setDebug(*instruction)->extract();
				auto iter = store->rs->registers.begin();
				for (size_t i = 0; i < register_count; ++i) {
					VariablePtr var = function.makePrecoloredVariable(*iter++, instruction->parent.lock());
					function.insertBefore(instruction, std::make_shared<StoreRInstruction>(var, m3))
						->setDebug(*instruction)->extract();
					if (iter != store->rs->registers.end())
						function.insertBefore(instruction, std::make_shared<AddIInstruction>(m3, 8, m3))
							->setDebug(*instruction)->extract();
				}
				to_remove.push_back(instruction);
			}
		}

		for (InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return changed;
	}
}
