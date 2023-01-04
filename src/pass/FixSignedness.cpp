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

#include <sstream>

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

		operator std::string() const {
			std::ostringstream ss;
			ss << '(' << position << ", ";
			if (operand)
				ss << *operand;
			else
				ss << "\e[1mnull\e[22m";
			ss << ')';
			return ss.str();
		}
	};

	std::ostream & operator<<(std::ostream &os, const ConflictTablePair &pair) {
		return os << std::string(pair);
	}
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
					// info() << "Offending instruction: " << old << " \e[1m!" << instruction->debugIndex << "\e[22m\n"
					//        << "\e[2m...\e[22m in function \e[1m" << *instruction->parent.lock()->parent->name
					//        << "\e[2m\n";
					// info() << "Types: " << *err.one << " and " << *err.two << '\n';
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

			last_changed = std::move(changed);
		} while (any_changed);

		success() << *function.name << '\n';

		if (last_changed.empty())
			return;

		warn() << "Some left over:\n";

		std::map<ConflictTablePair, std::vector<InstructionPtr>> conflict_map;

		for (const auto &instruction: last_changed) {
			std::cerr << "    " << instruction << '\n';
			if (auto r_type = std::dynamic_pointer_cast<RType>(instruction)) {
				conflict_map[{0, r_type->rs}].push_back(r_type);
				conflict_map[{1, r_type->rt}].push_back(r_type);
				conflict_map[{2, r_type->rd}].push_back(r_type);
			} else if (auto i_type = std::dynamic_pointer_cast<IType>(instruction)) {
				conflict_map[{0, i_type->rs}].push_back(i_type);
				conflict_map[{2, i_type->rd}].push_back(i_type);
			}
		}

		info() << "Checking conflicts.\n";

		for (auto iter = conflict_map.begin(), end = conflict_map.end(); iter != end; ++iter) {
			const auto &pair = iter->first;
			const auto &list = iter->second;
			if (1 < list.size()) {
				warn() << pair << ": size = " << list.size() << '\n';
				for (const auto &instruction: list)
					std::cerr << "    " << *instruction << '\n';
			}
		}
	}
}
