#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "compiler/Program.h"
#include "exception/SignednessSharingError.h"
#include "exception/TypeError.h"
#include "instruction/BitcastInstruction.h"
#include "instruction/ComparisonIInstruction.h"
#include "instruction/ComparisonRInstruction.h"
#include "instruction/MoveInstruction.h"
#include "pass/FixSignedness.h"
#include "util/Timer.h"

#include <sstream>

// #define DEBUG_FIXEDSIGNEDNESS

namespace LL2W {
	struct ConflictTablePair {
		int position;
		std::reference_wrapper<VariablePtr> operand;

		bool operator<(const ConflictTablePair &other) const {
			if (position < other.position)
				return true;
			if (position > other.position)
				return false;
			if (!operand.get() && other.operand.get())
				return true;
			if (!other.operand.get())
				return false;
			return operand.get()->id < other.operand.get()->id;
		}

		operator std::string() const {
			std::ostringstream ss;
			ss << '(' << position << ", ";
			if (operand.get())
				ss << *operand.get();
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
			if (pair.operand.get()) {
				std::string to_hash = *pair.operand.get()->id;
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
					// throw;
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

#ifdef DEBUG_FIXEDSIGNEDNESS
		success() << *function.name << '\n';
#endif

		if (last_changed.empty())
			return;

#ifdef DEBUG_FIXEDSIGNEDNESS
		warn() << "Some left over:\n";
#endif

		std::map<ConflictTablePair, std::list<InstructionPtr>> conflict_map;

		for (const auto &instruction: last_changed) {
#ifdef DEBUG_FIXEDSIGNEDNESS
			std::cerr << "    " << instruction << '\n';
#endif
			if (auto r_type = std::dynamic_pointer_cast<RType>(instruction)) {
				conflict_map[{0, r_type->rs}].push_back(r_type);
				conflict_map[{1, r_type->rt}].push_back(r_type);
				conflict_map[{2, r_type->rd}].push_back(r_type);
			} else if (auto i_type = std::dynamic_pointer_cast<IType>(instruction)) {
				conflict_map[{0, i_type->rs}].push_back(i_type);
				conflict_map[{2, i_type->rd}].push_back(i_type);
			}
		}

#ifdef DEBUG_FIXEDSIGNEDNESS
		info() << "Checking conflicts.\n";
#endif

		bool done = true;
		do {
			done = true;

			for (auto iter = conflict_map.begin(), end = conflict_map.end(); iter != end; ++iter) {
				auto &pair = iter->first;
				auto &list = iter->second;
				if (1 < list.size()) {
#ifdef DEBUG_FIXEDSIGNEDNESS
					warn() << pair << ": size = " << list.size() << '\n';
#endif
					for (auto iter = list.begin(); iter != list.end();) {
						const auto &instruction = *iter;
#ifdef DEBUG_FIXEDSIGNEDNESS
						std::cerr << "    " << *instruction << '\n';
#endif
						bool fixed = false;
						try {
							fixed = instruction->fixSignedness();
						} catch (const SignednessSharingError &err) {}

						if (!fixed) {
							// If a fix does nothing or if attempting to fix causes a signedness sharing error, then we
							// have to bitcast to an alias with a type override.
							VariablePtr &operand = pair.operand;
							auto int_type = std::dynamic_pointer_cast<IntType>(operand->type);
							if (!int_type)
								throw TypeError("Not an IntType", operand->type);
							auto bitcast = BitcastInstruction::make(operand, function, int_type->invertedCopy(),
								instruction->parent.lock());
							operand = bitcast->rd;
							function.insertBefore(instruction, bitcast);
							++iter;
						} else
							list.erase(iter++);
					}
				}

				if (1 < list.size())
					done = false;
			}
		} while (!done);
	}
}
