#include <algorithm>
#include <fstream>
#include <optional>

#include "allocator/ColoringAllocator.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"
#include "graph/UncolorableError.h"
#include "pass/MakeCFG.h"
#include "pass/SplitBlocks.h"
#include "util/Util.h"

#define DEBUG_COLORING
#define CONSTRUCT_BY_BLOCK
// #define SELECT_LOWEST_COST

namespace LL2W {
	ColoringAllocator::Result ColoringAllocator::attempt() {
		++attempts;
#ifdef DEBUG_COLORING
		std::cerr << "Allocating for \e[1m" << *function->name << "\e[22m.\n";
#endif
		if (!argumentsPrecolored)
			function->precolorArguments();

		makeInterferenceGraph();
		try {
			interference.color(Graph::ColoringAlgorithm::Greedy, WhyInfo::temporaryOffset,
				WhyInfo::savedOffset + WhyInfo::savedCount - 1);
		} catch (const UncolorableError &err) {
#ifdef DEBUG_COLORING
			std::cerr << "Coloring failed.\n";
#endif
			int highest_degree = -1;
#ifdef SELECT_LOWEST_COST
			VariablePtr to_spill = selectLowestSpillCost();
			(void) highest_degree;
#else
			VariablePtr to_spill = selectHighestDegree(&highest_degree);
			if (highest_degree == -1)
				throw std::runtime_error("highest_degree is -1");
#endif

			if (!to_spill) {
				error() << "to_spill is null!\n";
				throw std::runtime_error("to_spill is null");
			}
#ifdef DEBUG_COLORING
			std::cerr << "Going to spill " << *to_spill;
#ifndef SELECT_LOWEST_COST
			std::cerr << " (degree: " << highest_degree << ")";
#endif
			std::cerr << ". Likely name: " << function->variableStore.size() << "\n";
#endif
			lastSpillAttempt = to_spill;
			triedIDs.insert(to_spill->id);
			triedLabels.insert(std::to_string(to_spill->id));
			if (function->spill(to_spill)) {
#ifdef DEBUG_COLORING
				std::cerr << "Spilled " << *to_spill << ". Variables: " << function->variableStore.size()
				          << ". Stack locations: " << function->stack.size() << "\n";
#endif
				lastSpill = to_spill;
				++spillCount;
				int split = Passes::splitBlocks(*function);
				if (0 < split) {
#ifdef DEBUG_COLORING
					std::cerr << split << " block" << (split == 1? " was" : "s were") << " split.\n";
#endif
					for (BasicBlockPtr &block: function->blocks)
						block->extract();
					Passes::makeCFG(*function);
					function->extractVariables(true);
					function->resetLiveness();
					function->computeLiveness();
				}
#ifdef DEBUG_COLORING
				else std::cerr << "No blocks were split.\n";
#endif
				if (highest_degree == 397) {
					info() << "Edge count: " << interference.allEdges().size() << "\n";
					info() << "Vertex count: " << interference.size() << "\n";
					// interference.renderTo("/home/kai/interference.pdf");
					// function->debug();
				}
				return Result::Spilled;
			}
#ifdef DEBUG_COLORING
			else std::cerr << *to_spill << " wasn't spilled.\n";
#endif
			return Result::NotSpilled;
		}

#ifdef DEBUG_COLORING
		std::cerr << "Spilling process complete. There " << (spillCount == 1? "was " : "were ") << spillCount << " "
		          << "spill" << (spillCount == 1? ".\n" : "s.\n");
#endif

		for (const std::pair<const std::string, Node *> &pair: interference) {
			VariablePtr ptr = pair.second->get<VariablePtr>();
#ifdef DEBUG_COLORING
			std::cerr << "Variable " << std::string(*ptr) << ": " << ptr->registersString() << " -> ( ";
			for (const int color: pair.second->colors) std::cerr << color << " ";
			std::cerr << ")\n";
#endif
			if (ptr->registers.empty()) {
				std::set<int> assigned;
				for (const int color: pair.second->colors)
					assigned.insert(color);
				ptr->setRegisters(assigned);
			}
		}

		return Result::Success;
	}

	VariablePtr ColoringAllocator::selectHighestDegree(int *degree_out) const {
		const Node *highest_node = nullptr;
		int highest = -1;
		// std::cerr << "Avoid["; for (const std::string &s: triedLabels) std::cerr << " " << s; std::cerr << " ]\n";
		for (const Node *node: interference.nodes()) {
			const int degree = node->degree();
			if (highest < degree && triedLabels.count(node->label()) == 0) {
				highest_node = node;
				highest = degree;
			}
		}

		if (highest_node == nullptr)
			throw std::runtime_error("Couldn't find node with highest degree out of " +
				std::to_string(interference.nodes().size()) + " node(s)");

		std::vector<const Node *> all_highest;
		for (const Node *node: interference.nodes())
			if (node->degree() == static_cast<size_t>(highest))
				all_highest.push_back(node);

		if (degree_out)
			*degree_out = highest;

		// srand(time(nullptr));

		// return all_highest[rand() % all_highest.size()]->get<VariablePtr>();

		return highest_node->get<VariablePtr>();
	}

	VariablePtr ColoringAllocator::selectLowestSpillCost() const {
		VariablePtr ptr;
		int lowest = -1;
		for (const std::pair<const int, VariablePtr> &pair: function->variableStore) {
			const VariablePtr &var = pair.second;
			if (var->allRegistersSpecial())
				continue;
			var->clearSpillCost();
			const int cost = var->spillCost();
			if (cost != -1 && triedIDs.count(var->id) == 0 && (lowest == -1 || (cost < lowest && !var->isSimple()))) {
				lowest = cost;
				ptr = var;
			}
		}

		return ptr;
	}

// #undef DEBUG_COLORING

	void ColoringAllocator::makeInterferenceGraph() {
		interference.clear();
		size_t links = 0;

		for (const std::pair<const int, VariablePtr> &pair: function->variableStore) {
#ifdef DEBUG_COLORING
			// std::cerr << "%% " << pair.first << " " << *pair.second << "; aliases:";
			// for (Variable *v: pair.second->getAliases()) std::cerr << " " << *v;
			// std::cerr << "\n";
#endif
			if (pair.second->registers.empty()) {
				const std::string id = std::to_string(pair.second->id);
				if (!interference.hasLabel(id)) { // Use only one variable from a set of aliases.
					Node &node = interference.addNode(id);
					node.data = pair.second;
#ifdef DEBUG_COLORING
					// info() << *pair.second << ": " << pair.second->registersRequired() << " required.";
					// if (pair.second->type)
					// 	std::cerr << " " << std::string(*pair.second->type);
					// std::cerr << "\n";
#endif
					node.colorsNeeded = pair.second->registersRequired();
				}
			}
		}

		std::vector<int> labels;
		labels.reserve(function->variableStore.size());
		for (const std::pair<const int, VariablePtr> &pair: function->variableStore)
			labels.push_back(pair.first);

#ifndef CONSTRUCT_BY_BLOCK
		// Maps a variable ID to a set of blocks in which the variable is live-in or live-out.
		std::map<int, std::unordered_set<int>> live;

		for (const std::pair<const int, VariablePtr> &pair: function->variableStore) {
			if (!pair.second->registers.empty())
				continue;
#ifdef DEBUG_COLORING
			std::cerr << "Variable " << *pair.second << ":\n";
#endif
			for (const std::weak_ptr<BasicBlock> &bptr: pair.second->definingBlocks) {
				live[pair.second->id].insert(bptr.lock()->index);
#ifdef DEBUG_COLORING
				std::cerr << "  definer: " << *bptr.lock()->label << " (" << bptr.lock()->index << ")\n";
#endif
			}
			for (const std::weak_ptr<BasicBlock> &bptr: pair.second->usingBlocks) {
				live[pair.second->id].insert(bptr.lock()->index);
#ifdef DEBUG_COLORING
				std::cerr << "  user: " << *bptr.lock()->label << " (" << bptr.lock()->index << ")\n";
#endif
			}
		}

		for (const std::shared_ptr<BasicBlock> &block: function->blocks) {
#ifdef DEBUG_COLORING
			if (!block)
				std::cerr << "block is null?\n";
#endif
			for (const VariablePtr &var: block->liveIn)
				if (var->registers.empty()) {
#ifdef DEBUG_COLORING
					std::cerr << "Variable " << *var << " is live-in at block " << *block->label << "\n";
#endif
					live[var->id].insert(block->index);
				}
			for (const VariablePtr &var: block->liveOut)
				if (var->registers.empty()) {
#ifdef DEBUG_COLORING
					std::cerr << "Variable " << *var << " is live-out at block " << *block->label << "\n";
#endif
					live[var->id].insert(block->index);
				}
		}

		if (1 < labels.size()) {
			const size_t size = labels.size();
#ifdef DEBUG_COLORING
			std::cerr << "Label count: " << size << "\n";
#endif
			size_t checks = 0;
			for (size_t i = 0; i < size - 1; ++i) {
				for (size_t j = i + 1; j < size; ++j) {
					VariablePtr left  = function->variableStore.at(labels[i]),
					            right = function->variableStore.at(labels[j]);
					if (left->id != right->id && Util::hasOverlap(live[left->id], live[right->id])) {
						interference.link(std::to_string(left->id), std::to_string(right->id), true);
						++links;
					}
					++checks;
				}
			}
#ifdef DEBUG_COLORING
			std::cerr << "Ran " << checks << " check" << (checks == 1? "" : "s") << ".\n";
#endif
		}

#else
		std::unordered_map<int, std::vector<int>> vecs;
		std::unordered_map<int, std::unordered_set<int>> sets;

		for (const std::pair<const int, VariablePtr> &pair: function->variableStore) {
			if (!pair.second->registers.empty())
				continue;
			for (const std::weak_ptr<BasicBlock> &bptr: pair.second->definingBlocks) {
				const int index = bptr.lock()->index;
				if (sets[index].count(pair.second->id) == 0) {
					vecs[index].push_back(pair.second->id);
					sets[index].insert(pair.second->id);
				}
			}
			for (const std::weak_ptr<BasicBlock> &bptr: pair.second->usingBlocks) {
				const int index = bptr.lock()->index;
				if (sets[index].count(pair.second->id) == 0) {
					vecs[index].push_back(pair.second->id);
					sets[index].insert(pair.second->id);
				}
			}
		}

		for (const std::shared_ptr<BasicBlock> &block: function->blocks) {
			std::vector<int> &vec = vecs[block->index];
			std::unordered_set<int> &set = sets[block->index];
			for (const VariablePtr &var: block->liveIn)
				if (var->registers.empty() && set.count(var->id) == 0) {
					vec.push_back(var->id);
					set.insert(var->id);
				}
			for (const VariablePtr &var: block->liveOut)
				if (var->registers.empty() && set.count(var->id) == 0) {
					vec.push_back(var->id);
					set.insert(var->id);
				}
		}

#ifdef DEBUG_COLORING
		std::cerr << "Label count: " << labels.size() << "\n";
#endif
		for (const std::pair<const int, std::vector<int>> &pair: vecs) {
			const size_t size = pair.second.size();
			if (size < 2)
				continue;
			for (size_t i = 0; i < size - 1; ++i)
				for (size_t j = i + 1; j < size; ++j) {
					interference.link(std::to_string(pair.second[i]), std::to_string(pair.second[j]), true);
					++links;
				}
		}
#endif

#ifdef DEBUG_COLORING
		std::cerr << "Made " << links << " link" << (links == 1? "" : "s") << ".\n";
#endif
	}
}
