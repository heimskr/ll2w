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
	struct ConflictTableKey {
		Role role;
		std::reference_wrapper<VariablePtr> operand;

		bool operator<(const ConflictTableKey &other) const {
			if (static_cast<int>(role) < static_cast<int>(other.role))
				return true;
			if (static_cast<int>(role) > static_cast<int>(other.role))
				return false;
			if (!operand.get() && other.operand.get())
				return true;
			if (!other.operand.get())
				return false;
			return operand.get()->id < other.operand.get()->id;
		}

		operator std::string() const {
			std::ostringstream ss;
			ss << '(' << (role == Role::Source? "src" : "dst") << ", ";
			if (operand.get())
				ss << *operand.get();
			else
				ss << "\e[1mnull\e[22m";
			ss << ')';
			return ss.str();
		}
	};

	std::ostream & operator<<(std::ostream &os, const ConflictTableKey &pair) {
		return os << std::string(pair);
	}
}

namespace std {
	template <>
	struct hash<LL2W::ConflictTableKey> {
		size_t operator()(const LL2W::ConflictTableKey &pair) const {
			if (pair.operand.get()) {
				std::string to_hash = *pair.operand.get()->id;
				to_hash += '!';
				return std::hash<std::string>()(to_hash + (pair.role == LL2W::Role::Source? "s" : "d"));
			}
			return static_cast<int>(pair.role);
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
					if (instruction->fixSignedness()) { // || instruction->typeMismatch()) {
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

		using MPVariant = std::variant<RType::RVariablePtr, IType::IVariablePtr>;

		std::map<ConflictTableKey, std::list<std::pair<InstructionPtr, MPVariant>>> conflict_map;

		for (const auto &instruction: last_changed) {
#ifdef DEBUG_FIXEDSIGNEDNESS
			std::cerr << "    " << instruction << '\n';
#endif
			if (auto r_type = std::dynamic_pointer_cast<RType>(instruction)) {
				if (r_type->rs)
					conflict_map[{r_type->rsRole(), r_type->rs}].emplace_back(r_type, &RType::rs);
				if (r_type->rt)
					conflict_map[{r_type->rtRole(), r_type->rt}].emplace_back(r_type, &RType::rt);
				if (r_type->rd)
					conflict_map[{r_type->rdRole(), r_type->rd}].emplace_back(r_type, &RType::rd);
			} else if (auto i_type = std::dynamic_pointer_cast<IType>(instruction)) {
				if (i_type->rs)
					conflict_map[{i_type->rsRole(), i_type->rs}].emplace_back(i_type, &IType::rs);
				if (i_type->rs)
					conflict_map[{i_type->rdRole(), i_type->rd}].emplace_back(i_type, &IType::rd);
			}
		}

#ifdef DEBUG_FIXEDSIGNEDNESS
		info() << "Checking conflicts.\n";
#endif

		bool done = true;
		do {
			done = true;

			for (auto map_iter = conflict_map.begin(), end = conflict_map.end(); map_iter != end; ++map_iter) {
				auto &list = map_iter->second;
				if (1 < list.size()) {
#ifdef DEBUG_FIXEDSIGNEDNESS
					warn() << key << ": size = " << list.size() << '\n';
#endif
					for (auto list_iter = list.begin(); list_iter != list.end();) {
						const auto &instruction = list_iter->first;
						const auto &variant = list_iter->second;
#ifdef DEBUG_FIXEDSIGNEDNESS
						std::cerr << "    " << *instruction << '\n';
#endif
						bool should_change = instruction->typeMismatch();

						if (should_change)
							error() << "Need to change " << *instruction << '\n';
						else
							success() << "No need to change " << *instruction << '\n';

						// if (!should_change) {
						// 	try {
						// 		instruction->fixSignedness();
						// 	} catch (const SignednessSharingError &) {
						// 		should_change = true;
						// 	}
						// }

						if (should_change) {
							// If a fix does nothing or if attempting to fix causes a signedness sharing error, then we
							// have to bitcast to an alias with a type override.
							VariablePtr *operand_ptr = nullptr;
							if (auto rtype = std::dynamic_pointer_cast<RType>(instruction)) {
								operand_ptr = &((*rtype).*std::get<RType::RVariablePtr>(variant));
								std::cerr << "          rs: " << &rtype->rs << '\n';
								std::cerr << "          rt: " << &rtype->rt << '\n';
								std::cerr << "          rd: " << &rtype->rd << '\n';
								std::cerr << "          mp: " << operand_ptr << " -> " << operand_ptr->get() << '\n';
							} else if (auto itype = std::dynamic_pointer_cast<IType>(instruction)) {
								operand_ptr = &((*itype).*std::get<IType::IVariablePtr>(variant));
								std::cerr << "          rs: " << &itype->rs << '\n';
								std::cerr << "          rd: " << &itype->rd << '\n';
								std::cerr << "          mp: " << operand_ptr << " -> " << operand_ptr->get() << '\n';
							} else
								throw std::runtime_error("Non-R-/I-type in FixSignedness");
							std::cerr << '\n';
							info() << "Instruction(" << *instruction << ")\n";
							VariablePtr &operand = *operand_ptr;
							TypePtr inverted_copy;

							if (auto int_type = std::dynamic_pointer_cast<IntType>(operand->type)) {
								inverted_copy = int_type->invertedCopy();
							} else if (auto ptr_type = std::dynamic_pointer_cast<PointerType>(operand->type)) {
								inverted_copy = ptr_type->invertedCopy();
							} else {
								error() << *operand->type << '\n';
								throw TypeError("Not an IntType or PointerType", operand->type);
							}
							info() << "Function: \e[1m" << *function.name << "\e[22m\n";
							info() << "Old instruction: " << instruction << " \e[1m!" << instruction->debugIndex << "\e[22m\n";
							auto bitcast = BitcastInstruction::make(operand, function, inverted_copy,
								instruction->parent.lock());
							bitcast->setDebug(*instruction)->extract();
							operand = bitcast->rd;
							info() << "New instruction: " << instruction << '\n';
							info() << "Bitcast:         " << *bitcast << " \e[1m!" << bitcast->debugIndex << "\e[22m\n";
							function.insertBefore(instruction, bitcast);
							++list_iter;
						} else
							list.erase(list_iter++);
					}
				}

				if (1 < list.size())
					done = false;
			}
		} while (!done);
	}
}
