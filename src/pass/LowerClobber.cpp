#include <algorithm>
#include <cassert>
#include <iostream>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "instruction/Clobber.h"
#include "instruction/MoveInstruction.h"
#include "instruction/SetInstruction.h"
#include "instruction/StackLoadInstruction.h"
#include "instruction/StackStoreInstruction.h"
#include "pass/LowerClobber.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	static bool isLive(const BasicBlockPtr &block, int reg) {
		assert(block != nullptr);
		return std::ranges::any_of(block->getAllLive(), [reg](const VariablePtr &var) {
			return var->registers.contains(reg);
		});
	}

	static bool isLive(const std::shared_ptr<Clobber> &clobber) {
		Timer timer{"Clobber::IsLive"};

		BasicBlockPtr block = clobber->parent.lock();
		const auto reg = clobber->reg;

		if (isLive(block, reg)) {
			return true;
		}

		// Sometimes a variable will be defined before the clobber but in the same block, and used after the clobber but
		// also in the same block. If the defining blocks count and the using blocks count are both 1, then the variable
		// will be considered not live anywhere, but it still needs to be clobbered.

		const auto clobber_index = clobber->index;

		for (const InstructionPtr &instruction: block->instructions) {
			// Don't look for definitions after the clobber,
			if (clobber_index <= instruction->index) {
				break;
			}

			for (const VariablePtr &written: instruction->written) {
				// Skip this variable if it's not assigned the clobbered register.
				if (!written->hasRegister(reg)) {
					continue;
				}

				// Skip this variable if it's defined in multiple blocks.
				if (written->definingBlocks.size() > 1) {
					continue;
				}

				// Skip this variable if it's not used anywhere.
				if (written->uses.empty()) {
					continue;
				}

				// Skip this variable if it has no definitions in this block before the clobber.
				if (!written->definitions.iterate([&](InstructionPtr &&definition) {
					return definition->parent.lock() == block && definition->index < clobber_index;
				})) {
					continue;
				}

				// Skip this variable if there are no uses in this block after the clobber.
				if (!written->uses.iterate([&](InstructionPtr &&use) {
					return use->parent.lock() == block && use->index > clobber_index;
				})) {
					continue;
				}

				return true;
			}
		}

		return false;
	}

	size_t lowerClobber(Function &function) {
		Timer timer{"LowerClobber"};
		std::vector<InstructionPtr> to_remove;

		for (const InstructionPtr &instruction: function.linearInstructions) {
			if (auto clobber = std::dynamic_pointer_cast<Clobber>(instruction)) {
				const int reg = clobber->reg;
				const std::string reg_name = WhyInfo::registerName(reg);
				assert(reg == clobber->unclobber->reg);
				if (isLive(clobber)) {
					// TODO: check liveness of register at unclobber location?
					VariablePtr precolored = function.makePrecoloredVariable(reg, instruction->parent.lock());
					const StackLocation *location = nullptr;

					if (function.clobbers.contains(reg)) {
						location = function.clobbers.at(reg);
					} else {
						location = &function.addToStack(precolored, StackLocation::Purpose::Clobber, 8, 8);
						function.clobbers.emplace(reg, location);
					}

					// const int offset = -location->offset;

					auto store = std::make_shared<StackStoreInstruction>(*location, precolored);
					auto load = std::make_shared<StackLoadInstruction>(precolored, *location);

					function.comment(clobber, "Clobber $" + reg_name, false);
					function.insertBefore(clobber, store, false)->setDebug(*instruction, false)->setSecret()->extract();
					function.comment(clobber->unclobber, "Unclobber $" + reg_name, false);
					function.insertBefore(clobber->unclobber, load, false)->setDebug(*instruction, true);
					for (const auto &semi: clobber->semis) {
						function.comment(semi, "Semiunclobber $" + reg_name + " into " + semi->destination->toString(), false);
						auto semi_load = std::make_shared<StackLoadInstruction>(semi->destination, *location);
						function.insertBefore(semi, semi_load, false)->setDebug(*semi, true);
					}
				} else {
					for (const auto &semi: clobber->semis) {
						function.comment(semi, "Semiunclobber $" + reg_name + " into " + semi->destination->toString(), false);
						auto precolored = function.makePrecoloredVariable(reg, instruction->parent.lock());
						// TODO(typed): consider inserting an assertion to validate type nonnullness.
						precolored->type = semi->destination->type;
						function.insertBefore<MoveInstruction, false>(semi, precolored, semi->destination);
					}
				}

				to_remove.push_back(clobber);
				to_remove.push_back(clobber->unclobber);
				for (const auto &semi: clobber->semis) {
					to_remove.push_back(semi);
				}
			}
		}

		for (const InstructionPtr &instruction: to_remove) {
			function.remove(instruction, false);
		}

		if (!to_remove.empty()) {
			function.reindexInstructions();
		}

		return to_remove.size();
	}
}
