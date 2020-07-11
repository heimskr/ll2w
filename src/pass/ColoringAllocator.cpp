#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"
#include "graph/UncolorableError.h"
#include "pass/ColoringAllocator.h"
#include "util/Util.h"

namespace LL2W::Passes {
	int allocateColoring(Function &function) {
		int spill_count = 0;
		while (true) {
			Graph interference = makeInterferenceGraph(function);
			try {
				interference.color(Graph::ColoringAlgorithm::Greedy, WhyInfo::temporaryOffset,
					WhyInfo::savedOffset + WhyInfo::savedCount - 1);
			} catch (const UncolorableError &err) {
				// spill
				VariablePtr to_spill = selectLowestSpillCost(function);
				std::cout << "Going to spill " << *to_spill << ". " << function.variableStore.size() << "\n";
				function.addToStack(to_spill, StackLocation::Purpose::Spill);
				if (function.spill(to_spill)) {
					std::cout << "Spilled. " << function.variableStore.size() << "\n";
					++spill_count;
				} else std::cout << "Not spilled.\n";
				continue;
			}
			break;
		}

		return 0;
	}

	VariablePtr selectLowestSpillCost(Function &function) {
		VariablePtr ptr = function.variableStore.begin()->second;
		int lowest = ptr->spillCost();
		for (const std::pair<int, VariablePtr> &pair: function.variableStore) {
			const VariablePtr &var = pair.second;
			var->clearSpillCost();
			const int cost = var->spillCost();
			if (cost < lowest && !var->isSimple()) {
				lowest = cost;
				ptr = var;
			}
		}

		return ptr;
	}

	Graph makeInterferenceGraph(Function &function) {
		Graph graph;
		for (const std::pair<int, VariablePtr> &pair: function.variableStore)
			graph += std::to_string(pair.second->id);

		std::vector<int> labels;
		labels.reserve(function.variableStore.size());
		for (const std::pair<int, VariablePtr> &pair: function.variableStore)
			labels.push_back(pair.first);

		std::map<int, std::unordered_set<int>> live;

		for (const std::pair<int, VariablePtr> &pair: function.variableStore) {
			std::cout << *pair.second << "!\n";
			for (const BasicBlockPtr &bptr: pair.second->definingBlocks)
				live[pair.second->id].insert(bptr->index);
			for (const BasicBlockPtr &bptr: pair.second->usingBlocks)
				live[pair.second->id].insert(bptr->index);
		}

		for (const BasicBlockPtr &block: function.blocks) {
			for (const VariablePtr var: block->liveIn)
				live[var->id].insert(block->index);
			for (const VariablePtr var: block->liveOut)
				live[var->id].insert(block->index);
		}


		if (1 < labels.size()) {
			const size_t size = labels.size();
			for (size_t i = 0; i < size - 1; ++i) {
				for (size_t j = i + 1; j < size; ++j) {
					VariablePtr left  = function.variableStore.at(labels[i]),
					            right = function.variableStore.at(labels[j]);
					// std::cout << "Left  (" << left->id << "):";  for (const auto x: live[left->id])  std::cout << " " << x; std::cout << "\n";
					// std::cout << "Right (" << right->id << "):"; for (const auto x: live[right->id]) std::cout << " " << x; std::cout << "\n";
					if (hasOverlap(live[left->id], live[right->id]))
						graph.link(std::to_string(left->id), std::to_string(right->id), true);
				}
			}
		}

		// std::cout << ("RENDER: interference_" + *function.name + ".png") << "\n";
		// graph.renderTo("interference_" + *function.name + ".png");
		return graph;
	}
}
