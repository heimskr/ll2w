#include <algorithm>
#include <fstream>
#include <optional>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"
#include "graph/UncolorableError.h"
#include "pass/ColoringAllocator.h"
#include "pass/MakeCFG.h"
#include "pass/SplitBlocks.h"
#include "util/Util.h"

#define DEBUG_COLORING
#define CONSTRUCT_BY_BLOCK
// #define SELECT_LOWEST_COST

namespace LL2W::Passes {
	int allocateColoring(Function &function) {
#ifdef DEBUG_COLORING
		std::cerr << "Allocating for \e[1m" << *function.name << "\e[22m.\n";
#endif
		int spill_count = 0;
		std::unordered_set<int> tried;
		std::unordered_set<std::string> tried_labels;
		Graph interference;
		function.precolorArguments();
		while (true) {
			makeInterferenceGraph(function, interference);
			try {
				interference.color(Graph::ColoringAlgorithm::Greedy, WhyInfo::temporaryOffset,
					WhyInfo::savedOffset + WhyInfo::savedCount - 1);
			} catch (const UncolorableError &err) {
#ifdef DEBUG_COLORING
				std::cerr << "Coloring failed.\n";
#endif
#ifdef SELECT_LOWEST_COST
				VariablePtr to_spill = selectLowestSpillCost(function, tried);
#else
				VariablePtr to_spill = selectHighestDegree(interference, tried_labels);
#endif

				if (!to_spill) {
#ifdef DEBUG_COLORING
					std::cerr << "to_spill is null!\n";
#endif
					std::terminate();
				}
#ifdef DEBUG_COLORING
				std::cerr << "Going to spill " << *to_spill << ". " << function.variableStore.size() << "\n";
#endif
				tried.insert(to_spill->id);
				tried_labels.insert(std::to_string(to_spill->id));
				function.addToStack(to_spill, StackLocation::Purpose::Spill);
				if (function.spill(to_spill)) {
#ifdef DEBUG_COLORING
					std::cerr << "Spilled " << *to_spill << ". Variables: " << function.variableStore.size()
					          << ". Stack locations: " << function.stack.size() << "\n";
#endif
					++spill_count;
					int split = Passes::splitBlocks(function);
					if (0 < split) {
#ifdef DEBUG_COLORING
						std::cerr << split << " block" << (split == 1? " was" : "s were") << " split.\n";
#endif
						for (BasicBlockPtr &block: function.blocks)
							block->extract();
						Passes::makeCFG(function);
						function.extractVariables(true);
						function.resetLiveness();
						function.computeLiveness();
					}
#ifdef DEBUG_COLORING
					else std::cerr << "No blocks were split.\n";
#endif
				}
#ifdef DEBUG_COLORING
				else std::cerr << *to_spill << " wasn't spilled.\n";
#endif
				continue;
			}
			break;
		}

#ifdef DEBUG_COLORING
		std::cerr << "Spilling process complete. There " << (spill_count == 1? "was " : "were ") << spill_count << " "
		          << "spill" << (spill_count == 1? ".\n" : "s.\n");
#endif

		for (const std::pair<const std::string, Node *> &pair: interference) {
			VariablePtr ptr = pair.second->get<VariablePtr>();
			if (ptr->reg == -1)
				ptr->setRegister(pair.second->color);
		}

		return spill_count;
	}

	VariablePtr selectHighestDegree(Graph &interference, const std::unordered_set<std::string> &avoid) {
		Node *highest_node;
		int highest = -1;
		std::cerr << "Avoid["; for (const std::string &s: avoid) std::cerr << " " << s; std::cerr << "]\n";
		for (Node *node: interference.nodes()) {
			const int degree = node->degree();
			if (highest < degree && avoid.count(node->label()) == 0) {
				highest_node = node;
				highest = degree;
			}
		}

		return highest_node->get<VariablePtr>();
	}

	VariablePtr selectLowestSpillCost(Function &function, const std::unordered_set<int> &avoid) {
		VariablePtr ptr;
		int lowest = -1;
		for (const std::pair<const int, VariablePtr> &pair: function.variableStore) {
			const VariablePtr &var = pair.second;
			if (var->reg != -1 && WhyInfo::isSpecialPurpose(var->reg))
				continue;
			var->clearSpillCost();
			const int cost = var->spillCost();
			if (cost != -1 && avoid.count(var->id) == 0 && (lowest == -1 || (cost < lowest && !var->isSimple()))) {
				lowest = cost;
				ptr = var;
			}
		}

		return ptr;
	}

#undef DEBUG_COLORING

	void makeInterferenceGraph(Function &function, Graph &graph) {
		graph.clear();
		size_t links = 0;

		for (const std::pair<const int, VariablePtr> &pair: function.variableStore) {
#ifdef DEBUG_COLORING
			std::cerr << "%% " << pair.first << " " << *pair.second << "; aliases:";
			for (Variable *v: pair.second->getAliases()) std::cerr << " " << *v;
			std::cerr << "\n";
#endif
			if (pair.second->reg == -1) {
				const std::string id = std::to_string(pair.second->id);
				if (!graph.hasLabel(id)) { // Use only one variable from a set of aliases.
					Node &node = graph.addNode(id);
					node.data = pair.second;
				}
			}
		}

		std::vector<int> labels;
		labels.reserve(function.variableStore.size());
		for (const std::pair<const int, VariablePtr> &pair: function.variableStore)
			labels.push_back(pair.first);

#ifndef CONSTRUCT_BY_BLOCK
		std::map<int, std::unordered_set<int>> live;

		for (const std::pair<const int, VariablePtr> &pair: function.variableStore) {
			if (pair.second->reg != -1)
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

		for (const std::shared_ptr<BasicBlock> &block: function.blocks) {
#ifdef DEBUG_COLORING
			if (!block)
				std::cerr << "block is null?\n";
#endif
			for (const VariablePtr &var: block->liveIn)
				if (var->reg == -1) {
#ifdef DEBUG_COLORING
					std::cerr << "Variable " << *var << " is live-in at block " << *block->label << "\n";
#endif
					live[var->id].insert(block->index);
				}
			for (const VariablePtr &var: block->liveOut)
				if (var->reg == -1) {
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
					VariablePtr left  = function.variableStore.at(labels[i]),
					            right = function.variableStore.at(labels[j]);
					if (left->id != right->id && hasOverlap(live[left->id], live[right->id])) {
						graph.link(std::to_string(left->id), std::to_string(right->id), true);
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

		for (const std::pair<const int, VariablePtr> &pair: function.variableStore) {
			if (pair.second->reg != -1)
				continue;
			for (const std::weak_ptr<BasicBlock> &bptr: pair.second->definingBlocks) {
				const int index = bptr.lock()->index;
				if (sets[index].count(pair.second->id) == 0)
					vecs[index].push_back(pair.second->id);
			}
			for (const std::weak_ptr<BasicBlock> &bptr: pair.second->usingBlocks) {
				const int index = bptr.lock()->index;
				if (sets[index].count(pair.second->id) == 0)
					vecs[index].push_back(pair.second->id);
			}
		}

		for (const std::shared_ptr<BasicBlock> &block: function.blocks) {
			std::vector<int> &vec = vecs[block->index];
			std::unordered_set<int> &set = sets[block->index];
			for (const VariablePtr &var: block->liveIn)
				if (var->reg == -1 && set.count(var->id) == 0)
					vec.push_back(var->id);
			for (const VariablePtr &var: block->liveOut)
				if (var->reg == -1 && set.count(var->id) == 0)
					vec.push_back(var->id);
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
					graph.link(std::to_string(pair.second[i]), std::to_string(pair.second[j]), true);
					++links;
				}
		}
#endif

#ifdef DEBUG_COLORING
		std::cerr << "Made " << links << " link" << (links == 1? "" : "s") << ".\n";
#endif
	}
}
