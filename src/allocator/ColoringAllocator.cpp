#include <algorithm>
#include <climits>
#include <fstream>
#include <optional>

#include "allocator/ColoringAllocator.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"
#include "exception/NoChoiceError.h"
#include "graph/UncolorableError.h"
#include "instruction/IntermediateInstruction.h"
#include "pass/MakeCFG.h"
#include "pass/SplitBlocks.h"
#include "util/Timer.h"
#include "util/Util.h"

// #define DEBUG_COLORING
#define CONSTRUCT_BY_BLOCK
// #define SELECT_LOWEST_COST
#define SELECT_MOST_LIVE
// #define SELECT_CHAITIN

namespace LL2W {
	ColoringAllocator::ColoringAllocator(Function &function):
		Allocator(function),
		interference("interference graph for " + *function.name) {}

	Allocator::Result ColoringAllocator::firstAttempt() {
		makeInterferenceGraph();
		return attempt();
	}

	Allocator::Result ColoringAllocator::attempt() {
		return attemptOld();

		Timer timer{"ColoringAllocator::attempt"};

		constexpr int max_batch_size = 8;

		std::vector<VariablePtr> batch;

		Graph clone = interference;

		for (int i = 0; i < max_batch_size; ++i) {
			try {
				Timer timer{"GraphColor"};
				clone.color(Graph::ColoringAlgorithm::Greedy, WhyInfo::temporaryOffset, WhyInfo::savedOffset + WhyInfo::savedCount - 1);
				break;
			} catch (const UncolorableError &) {
				VariablePtr to_spill = select();
				lastSpillAttempt = to_spill;
				triedIDs.insert(to_spill->id);
				triedLabels.insert(*to_spill->id);
				clone -= *to_spill->id;
				batch.emplace_back(std::move(to_spill));
			}
		}

		if (batch.empty()) {
			return Result::Success;
		}

		if (auto count = function->spillBatch(batch, true); count > 0) {
			spillCount += count;
			info() << "Spilled.\n";
			makeInterferenceGraph();
			info() << "Remade.\n";
			return Result::Spilled;
		}

		info() << "Didn't spill.\n";
		return Result::NotSpilled;
	}

	VariablePtr ColoringAllocator::select() const {
#ifdef SELECT_LOWEST_COST
		VariablePtr to_spill = selectLowestSpillCost();
#elif defined(SELECT_CHAITIN)
		VariablePtr to_spill = selectChaitin();
#elif defined(SELECT_MOST_LIVE)
		VariablePtr to_spill = selectMostLive();
#else
		int highest_degree = -1;
		VariablePtr to_spill = selectHighestDegree(&highest_degree);
		if (highest_degree == -1) {
			throw std::runtime_error("highest_degree is -1");
		}
#endif
		if (!to_spill) {
			throw std::runtime_error("to_spill is null");
		}

		return to_spill;
	}

	Allocator::Result ColoringAllocator::attemptOld() {
		++attempts;
#ifdef DEBUG_COLORING
		std::cerr << "Allocating for \e[1m" << *function->name << "\e[22m.\n";
#endif

		Timer timer{"ColoringAllocator::attemptOld"};

		try {
			Timer timer{"GraphColor"};
			interference.color(Graph::ColoringAlgorithm::Greedy, WhyInfo::temporaryOffset, WhyInfo::savedOffset + WhyInfo::savedCount - 1);
		} catch (const UncolorableError &err) {
#ifdef DEBUG_COLORING
			std::cerr << "Coloring failed.\n";
#endif
			int highest_degree = -1;
#ifdef SELECT_LOWEST_COST
			VariablePtr to_spill = selectLowestSpillCost();
			(void) highest_degree;
#elif defined(SELECT_CHAITIN)
			VariablePtr to_spill = selectChaitin();
			(void) highest_degree;
#elif defined(SELECT_MOST_LIVE)
			VariablePtr to_spill = selectMostLive();
			(void) highest_degree;
#else
			VariablePtr to_spill = selectHighestDegree(&highest_degree);
			if (highest_degree == -1) {
				throw std::runtime_error("highest_degree is -1");
			}
#endif
			if (!to_spill) {
				error() << "to_spill is null!\n";
				throw std::runtime_error("to_spill is null");
			}
#ifdef DEBUG_COLORING
			info() << "Going to spill " << *to_spill;
#if !defined(SELECT_LOWEST_COST) && !defined(SELECT_MOST_LIVE) && !defined(SELECT_CHAITIN)
			std::cerr << " (degree: " << highest_degree << ")";
#endif
			std::cerr << ". Likely name: " << function->variableStore.size() << "\n";
			info() << "Can spill: " << std::boolalpha << function->canSpill(to_spill) << "\n";
#endif
			triedIDs.insert(to_spill->originalID);
			triedLabels.insert(*to_spill->originalID);
#ifdef DEBUG_COLORING
			info() << "Variable before climbing parents: " << *to_spill << " (OID: " << to_spill->originalID << ")\n";
#endif
			while (auto sparent = to_spill->getParent().lock()) {
				to_spill = sparent;
			}
#ifdef DEBUG_COLORING
			info() << "Variable after climbing parents: " << *to_spill << " (OID: " << to_spill->originalID << ")\n";
#endif
			lastSpillAttempt = to_spill;
			triedIDs.insert(to_spill->id);
			triedLabels.insert(*to_spill->id);

			if (function->spill(to_spill)) {
#ifdef DEBUG_COLORING
				std::cerr << "Spilled " << *to_spill << ". Variables: " << function->variableStore.size()
				          << ". Stack locations: " << function->stack.size() << "\n";
#endif
				lastSpill = to_spill;
				++spillCount;
				int split = 0;
				Passes::splitBlocks(*function);
				if (0 < split) {
#ifdef DEBUG_COLORING
					std::cerr << split << " block" << (split == 1? " was" : "s were") << " split.\n";
#endif
					for (BasicBlockPtr &block: function->blocks) {
						block->extract();
					}
					Passes::makeCFG(*function);
					function->extractVariables(true);
					function->resetLiveness();
					function->computeLiveness();
				}
#ifdef DEBUG_COLORING
				else std::cerr << "No blocks were split.\n";
#endif
				return Result::Spilled;
			}
#ifdef DEBUG_COLORING
			else std::cerr << *to_spill << " wasn't spilled.\n";
#endif
			return Result::NotSpilled;
		}

#ifdef DEBUG_COLORING
		info() << "Spilling process complete. There " << (spillCount == 1? "was " : "were ") << spillCount << " spill" << (spillCount == 1? ".\n" : "s.\n");
#endif

		for (const std::pair<const std::string, Node *> &pair: interference) {
			if (!pair.second->data.has_value()) {
				continue;
			}

			auto ptr = pair.second->get<VariablePtr>();
#ifdef DEBUG_COLORING
			std::cerr << "Variable " << std::string(*ptr) << ": " << ptr->registersString() << " -> ( ";
			for (const int color: pair.second->colors) {
				std::cerr << color << ' ';
			}
			std::cerr << ") a =";
			for (const Variable *alias: ptr->getAliases()) {
				std::cerr << ' ' << *alias;
			}
			std::cerr << '\n';
#endif
			if (ptr->registers.empty()) {
				const auto &colors = pair.second->colors;
				ptr->setRegisters({colors.begin(), colors.end()});
			}
		}

		return Result::Success;
	}

	VariablePtr ColoringAllocator::selectHighestDegree(int *degree_out) const {
		const Node *highest_node = nullptr;
		size_t highest = SIZE_MAX;
		// std::cerr << "Avoid["; for (const std::string &s: triedLabels) std::cerr << " " << s; std::cerr << " ]\n";
		for (const Node *node: interference.nodes()) {
			const size_t degree = node->degree();
			// if (highest < degree && triedLabels.count(node->label()) == 0) {
			// if (highest < degree && function->canSpill(node->get<VariablePtr>())) {
			if (highest == SIZE_MAX || (highest < degree && !triedLabels.contains(node->label()) && function->canSpill(node->get<VariablePtr>()))) {
				highest_node = node;
				highest = degree;
			}
		}

		if (highest_node == nullptr) {
			throw NoChoiceError("Couldn't find node with highest degree out of " + std::to_string(interference.nodes().size()) + " node(s)");
		}

		std::vector<const Node *> all_highest;
		for (const Node *node: interference.nodes()) {
			if (node->degree() == static_cast<size_t>(highest)) {
				all_highest.push_back(node);
			}
		}

		if (degree_out != nullptr) {
			*degree_out = highest;
		}

		return highest_node->get<VariablePtr>();
	}

	VariablePtr ColoringAllocator::selectChaitin() const {
		VariablePtr out;
		double lowest = std::numeric_limits<double>::infinity();

		for (const Node *node: interference.nodes()) {
			if (!node->data.has_value()) {
				continue;
			}

			auto &var = node->get<VariablePtr>();
			if (var->allRegistersSpecial() || !function->canSpill(var)) {
				continue;
			}
			var->clearSpillCost();
			const auto cost = var->spillCost();
			if (cost == INT64_MAX) {
				continue;
			}
			const size_t degree = node->degree();
			assert(degree > 0);
			const double chaitin = static_cast<double>(cost) / degree;
			if (chaitin < lowest) {
				lowest = chaitin;
				out = var;
			}
		}

		if (!out) {
			function->debug();
			throw NoChoiceError("Couldn't select a variable in ColoringAllocator::selectChaitin.");
		}

		return out;
	}

// #undef DEBUG_COLORING

	void ColoringAllocator::afterSpill(VariablePtr spilled_var, std::span<VariablePtr> new_vars) {
		Timer timer{"ColoringAllocator::afterSpill"};

		for (const auto &[label, node]: interference) {
			if (!node->data.has_value()) {
				continue;
			}

			VariablePtr var = std::any_cast<VariablePtr>(node->data);
			if (!var->allRegistersSpecial()) {
				node->colors.clear();
			}
		}

		Node &spilled_node = interference[*spilled_var->id];
		spilled_node.unlink();

		std::vector<Node *> new_nodes;
		new_nodes.reserve(new_vars.size());

		for (const VariablePtr &new_var: new_vars) {
			Node &new_node = interference.addNode(*new_var->id);
			new_node.data = new_var;
			new_node.colors = {new_var->registers.cbegin(), new_var->registers.cend()};
			new_node.colorsNeeded = new_var->registersRequired();
			new_nodes.emplace_back(&new_node);
		}

		size_t i = 0;
		for (const VariablePtr &new_var: new_vars) {
			Node &new_node = *new_nodes[i++];

			auto visit_block = [&](BasicBlockPtr block) {
				for (VariablePtr mentioned: block->mentioned) {
					mentioned = mentioned->climbParents();
					if (mentioned != new_var && !mentioned->allRegistersSpecial()) {
						Node &mentioned_node = interference[*mentioned->id];
						mentioned_node.colors.clear();
						new_node.link(mentioned_node, true);
					}
				}
			};

			BasicBlockPtr definer = new_var->onlyDefiner();
			// try {
				visit_block(definer);
			// } catch (const std::out_of_range &) {
			// 	interference.renderTo("interference_OOR.svg");
			// 	throw;
			// }

			for (const auto &weak_user: new_var->usingBlocks) {
				if (BasicBlockPtr user = weak_user.lock(); user && user != definer) {
					visit_block(user);
				}
			}
		}

		for (const auto &weak_definer: spilled_var->definingBlocks) {
			if (BasicBlockPtr definer = weak_definer.lock()) {
				for (VariablePtr mentioned: definer->mentioned) {
					mentioned = mentioned->climbParents();
					if (mentioned != spilled_var && !mentioned->allRegistersSpecial()) {
						Node &mentioned_node = interference[*mentioned->id];
						mentioned_node.colors.clear();
						spilled_node.link(mentioned_node, true);
					}
				}
			}
		}
	}

	void ColoringAllocator::makeInterferenceGraph() {
		Timer timer("MakeInterferenceGraph");
		interference.clear();
#ifdef DEBUG_COLORING
		size_t links = 0;
#endif

		for (const auto &[id, var]: function->variableStore) {
#ifdef DEBUG_COLORING_2
			std::cerr << "%% " << *id << ' ' << *var << "; aliases:";
			for (Variable *alias: var->getAliases()) {
				std::cerr << ' ' << *alias;
			}
			std::cerr << '\n';
#endif
			const std::string *parent_id = var->parentID();
			if (!interference.hasLabel(*parent_id)) { // Use only one variable from a set of aliases.
				Node &node = interference.addNode(*parent_id);
				node.data = var;
				node.colors = {var->registers.cbegin(), var->registers.cend()};
				node.colorsNeeded = var->registersRequired();
#ifdef DEBUG_COLORING_2
				info() << *var << ": " << var->registersRequired() << " required.";
				if (var->type) {
					std::cerr << " " << std::string(*var->type);
				}
				std::cerr << "\n";
#endif
#ifdef DEBUG_COLORING_2
			} else {
				// std::cerr << "Skipping " << *var << " (" << *id << "): parent (" << *parent_id << ") is in graph\n";
#endif
			}
		}


#ifndef CONSTRUCT_BY_BLOCK
		std::vector<Variable::ID> labels;
		labels.reserve(function->variableStore.size());
		for (const auto &[id, var]: function->variableStore) {
			labels.push_back(id);
		}

		// Maps a variable ID to a set of blocks in which the variable is live-in or live-out.
		std::map<Variable::ID, std::unordered_set<int>> live;

		for (const auto &[id, var]: function->variableStore) {
			if (!var->registers.empty()) {
				continue;
			}
#ifdef DEBUG_COLORING
			info() << "Variable " << *var << ":\n";
#endif
			for (const std::weak_ptr<BasicBlock> &bptr: var->definingBlocks) {
				live[var->id].insert(bptr.lock()->index);
#ifdef DEBUG_COLORING
				std::cerr << "  definer: " << *bptr.lock()->label << " (" << bptr.lock()->index << ")\n";
#endif
			}
			for (const std::weak_ptr<BasicBlock> &bptr: var->usingBlocks) {
				live[var->id].insert(bptr.lock()->index);
#ifdef DEBUG_COLORING
				std::cerr << "  user: " << *bptr.lock()->label << " (" << bptr.lock()->index << ")\n";
#endif
			}
		}

		for (const std::shared_ptr<BasicBlock> &block: function->blocks) {
#ifdef DEBUG_COLORING
			if (!block)
				warn() << "block is null?\n";
#endif
			for (const VariablePtr &var: block->liveIn)
				if (var->registers.empty()) {
#ifdef DEBUG_COLORING
					info() << "Variable " << *var << " is live-in at block " << *block->label << "\n";
#endif
					live[var->id].insert(block->index);
				}
			for (const VariablePtr &var: block->liveOut)
				if (var->registers.empty()) {
#ifdef DEBUG_COLORING
					info() << "Variable " << *var << " is live-out at block " << *block->label << "\n";
#endif
					live[var->id].insert(block->index);
				}
		}

		if (1 < labels.size()) {
			const size_t size = labels.size();
#ifdef DEBUG_COLORING
			info() << "Label count: " << size << "\n";
#endif
			size_t checks = 0;
			for (size_t i = 0; i < size - 1; ++i) {
				for (size_t j = i + 1; j < size; ++j) {
					VariablePtr left  = function->variableStore.at(labels[i]),
					            right = function->variableStore.at(labels[j]);
					if (left->id != right->id && Util::hasOverlap(live[left->id], live[right->id])) {
						interference.link(*left->id, *right->id, true);
						++links;
					}
					++checks;
				}
			}
#ifdef DEBUG_COLORING
			info() << "Ran " << checks << " check" << (checks == 1? "" : "s") << ".\n";
#endif
		}
#else
		std::unordered_map<int, std::vector<Variable::ID>> vecs;
		std::unordered_map<int, std::unordered_set<Variable::ID>> sets;

		for (const auto &[id, var]: function->variableStore) {
			const Variable::ID parent_id = var->parentID();

			if (var->allRegistersSpecial()) {
				continue;
			}

			static_assert(std::derived_from<BasicBlock, LivePoint>);
			static_assert(!std::derived_from<Instruction, LivePoint>);
			for (const auto &weak_def: var->definingBlocks) {
				const auto index = weak_def.lock()->index;
				if (sets[index].emplace(parent_id).second) {
					vecs[index].emplace_back(parent_id);
				}
			}

			for (const auto &weak_use: var->usingBlocks) {
				const auto index = weak_use.lock()->index;
				if (sets[index].emplace(parent_id).second) {
					vecs[index].emplace_back(parent_id);
				}
			}
		}

		for (const auto &live_point: function->livePoints) {
			auto index = live_point->getIndex();
			auto &vec = vecs[index];
			auto &set = sets[index];
			for (const VariablePtr &var: live_point->getAllLive()) {
				if (var->allRegistersSpecial()) {
					continue;
				}

				const Variable::ID parent_id = var->parentID();
				if (set.emplace(parent_id).second) {
					vec.emplace_back(parent_id);
				}
			}
		}

		for (const auto &[block_id, vec]: vecs) {
			const size_t size = vec.size();
			if (size < 2) {
				continue;
			}
			for (size_t i = 0; i < size - 1; ++i) {
				for (size_t j = i + 1; j < size; ++j) {
					interference.link(*vec[i], *vec[j], true);
#ifdef DEBUG_COLORING
					++links;
#endif
				}
			}
		}
#endif

		cachedPrecolored.clear();

		// With all that out of the way, we have to add some precolored nodes to tell the graph coloring algorithm not
		// to assign certain registers to certain variables. As of this writing, only unclobber instructions cause
		// precolored nodes to be made.
		int precolored_added = 0;
		for (const InstructionPtr &instruction: function->linearInstructions) {
			if (auto intermediate = std::dynamic_pointer_cast<IntermediateInstruction>(instruction)) {
				// TODO: maybe we'll have to care about precoloredReads someday. Probably not.
				intermediate->extractPrecolored();
				const auto &written = intermediate->precoloredWritten;
				if (written.empty()) {
					continue;
				}

				std::set<int> set{written.begin(), written.end()};

				Node *node = nullptr;

				if (auto iter = cachedPrecolored.find(set); iter != cachedPrecolored.end()) {
					node = iter->second;
				} else {
					std::string label = "__ll2w_pc" + std::to_string(precolored_added++);
					node = &interference.addNode(std::move(label));
					node->colors = set;
					cachedPrecolored.emplace(std::move(set), node);
				}

				for (const VariablePtr &var: intermediate->parent.lock()->getAllLive()) {
					const auto &pid = *var->parentID();
					if (interference.hasLabel(pid)) {
						node->link(interference[pid], true);
#ifdef DEBUG_COLORING
						++links;
#endif
					}
				}
			}
		}

#ifdef DEBUG_COLORING
		std::cerr << "Made " << links << " link" << (links == 1? "" : "s") << ".\n";
#endif
	}
}
