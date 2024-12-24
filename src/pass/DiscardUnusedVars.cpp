#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "instruction/Comment.h"
#include "pass/DiscardUnusedVars.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	static bool canDiscard(const VariablePtr &var) {
		if (var->usingBlocks.empty()) {
			return true;
		}

		if (var->definingBlocks.size() != 1 || var->usingBlocks.size() != 1) {
			return false;
		}

		BasicBlockPtr definer = var->definingBlocks.begin()->lock();
		if (!definer) {
			return false;
		}

		BasicBlockPtr user = var->usingBlocks.begin()->lock();
		if (!user) {
			return false;
		}

		assert(definer == user);
		return false;
	}

	size_t discardUnusedVars(Function &function) {
		Timer timer{"DiscardUnusedVars"};

		size_t discarded = 0;
		std::list<InstructionPtr> to_remove;

		for (const auto &[var_id, var]: function.variableStore) {
			if (!var->hasSpecialRegister() && !var->definitions.empty()) {
				if (function.isLiveOutAnywhere(var)) {
					continue;
				}

				if (!canDiscard(var)) {
					continue;
				}

				++discarded;
				// info() << "Discarding " << *var << " in " << *function.name << '\n';

				for (const auto &weak_definition: var->definitions) {
					if (InstructionPtr definition = weak_definition.lock()) {
						// std::cerr << "    " << *definition << '\n';
						to_remove.push_back(std::move(definition));
					}
				}
			}
		}

		for (const InstructionPtr &instruction: to_remove) {
			auto iter = std::find(function.linearInstructions.begin(), function.linearInstructions.end(), instruction);
			if (iter != function.linearInstructions.begin() && std::dynamic_pointer_cast<Comment>(*--iter)) {
				function.remove(*iter);
			}
			function.remove(instruction);
		}

		return discarded;
	}
}
