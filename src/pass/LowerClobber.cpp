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
	static bool isLive(const InstructionPtr &instruction, int reg) {
		BasicBlockPtr block = instruction->parent.lock();

		if (!block)
			throw std::runtime_error("Couldn't lock instruction block in LowerClobber");

		return std::ranges::any_of(block->allLive, [reg](const VariablePtr &var) {
			return var->registers.contains(reg);
		});
	}

	size_t lowerClobber(Function &function) {
		Timer timer("LowerClobber");
		std::list<InstructionPtr> to_remove;

		for (InstructionPtr &instruction: function.linearInstructions)
			if (auto clobber = std::dynamic_pointer_cast<Clobber>(instruction)) {
				const int reg = clobber->reg;
				assert(reg == clobber->unclobber->reg);
				if (isLive(instruction, reg)) {
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
					const std::string reg_name = '$' + WhyInfo::registerName(reg);

					auto store = std::make_shared<StackStoreInstruction>(*location, precolored);
					auto load = std::make_shared<StackLoadInstruction>(precolored, *location);

					function.comment(clobber, "Clobber " + reg_name);
					function.insertBefore(clobber, store, false)->setDebug(*instruction, false)->setSecret()->extract();
					function.comment(clobber->unclobber, "Unclobber " + reg_name);
					function.insertBefore(clobber->unclobber, load, false)->setDebug(*instruction, true);
					for (const auto &semi: clobber->semis) {
						function.comment(semi, "Semiunclobber " + reg_name + " into " + semi->destination->toString());
						auto semi_load = std::make_shared<StackLoadInstruction>(semi->destination, *location);
						function.insertBefore(semi, semi_load, false)->setDebug(*semi, true);
					}
				} else {
					for (const auto &semi: clobber->semis) {
						const std::string reg_name = WhyInfo::registerName(reg);
						function.comment(semi, "Semiunclobber $" + reg_name + " into " + semi->destination->toString());
						auto precolored = function.makePrecoloredVariable(reg, instruction->parent.lock());
						// TODO(typed): consider inserting an assertion to validate type nonnullness.
						precolored->type = semi->destination->type;
						function.insertBefore<MoveInstruction, false>(semi, precolored, semi->destination);
					}
				}

				// function.forceLiveness();

				to_remove.push_back(clobber);
				to_remove.push_back(clobber->unclobber);
				for (const auto &semi: clobber->semis)
					to_remove.push_back(semi);
			}

		function.reindexInstructions();

		for (const InstructionPtr &instruction: to_remove)
			function.remove(instruction);

		return to_remove.size();
	}
}
