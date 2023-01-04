#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "exception/SignednessSharingError.h"
#include "instruction/ComparisonIInstruction.h"
#include "instruction/ComparisonRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/FixSignedness.h"
#include "util/Timer.h"

namespace LL2W {
	struct ConflictTablePair {
		int position;
		VariablePtr operand;

		bool operator<(const ConflictTablePair &other) const {
			if (position < other.position)
				return true;
			if (position > other.position)
				return false;
			if (!operand && other.operand)
				return true;
			if (!other.operand)
				return false;
			return operand->id < other.operand->id;
		}
	};
}

namespace std {
	template <>
	struct hash<LL2W::ConflictTablePair> {
		size_t operator()(const LL2W::ConflictTablePair &pair) const {
			if (pair.operand) {
				std::string to_hash = *pair.operand->id;
				to_hash += '!';
				return std::hash<std::string>()(to_hash + std::to_string(pair.position));
			}
			return pair.position;
		}
	};
}

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
				} catch (const SignednessSharingError &err) {
					info() << "Offending instruction: " << old << " \e[1m!" << instruction->debugIndex << "\e[22m\n"
					       << "\e[2m...\e[22m in function \e[1m" << *instruction->parent.lock()->parent->name
					       << "\e[2m\n";
					info() << "Types: " << *err.one << " and " << *err.two << '\n';
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

		if (last_changed.empty())
			return;

		std::map<ConflictTablePair, std::vector<std::shared_ptr<RType>>> conflict_map_r;
		std::map<ConflictTablePair, std::vector<std::shared_ptr<IType>>> conflict_map_i;

		for (const auto &instruction: last_changed) {
			// if (auto
		}
	}
}
