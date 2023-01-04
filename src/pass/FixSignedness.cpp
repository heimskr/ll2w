#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "instruction/ComparisonIInstruction.h"
#include "instruction/ComparisonRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/FixSignedness.h"
#include "util/Timer.h"

namespace LL2W::Passes {
	void fixSignedness(Function &function) {
		Timer timer("FixSignedness");
		bool any_changed = false;
		std::vector<std::pair<std::string, std::string>> changed_pairs;
		std::unordered_set<InstructionPtr> last_changed;

		do {
			std::unordered_set<InstructionPtr> changed;
			// any_changed = false;
			changed_pairs.clear();

			for (InstructionPtr &instruction: function.linearInstructions) {
				const std::string old = instruction->debugExtra();
				try {
					if (instruction->fixSignedness()) {
						// any_changed = true;
						changed_pairs.emplace_back(old + " \e[1m!" + std::to_string(instruction->debugIndex) + "\e[22m",
							instruction->debugExtra());
						changed.insert(instruction);
					}
				} catch (const std::exception &) {
					info() << "Offending instruction: " << old << " \e[1m!" << instruction->debugIndex << "\e[22m\n";
					std::cerr << "... in function " << *instruction->parent.lock()->parent->name << '\n';
					throw;
				}
			}

			any_changed = !Util::equal(last_changed, changed);

			if (timer.difference() > std::chrono::seconds(20)) {
				function.debug();
				info() << "Last changed (" << changed.size() << "):\n";
				for (const auto &[o, n]: changed_pairs)
					std::cerr << "    " << o << "\n -> " << n << '\n';
				throw std::runtime_error("FixSignedness took too long");
			}

			last_changed = changed;
		} while (any_changed);
	}
}
