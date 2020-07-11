#include <optional>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/Variable.h"
#include "graph/UncolorableError.h"
#include "pass/ColoringAllocator.h"
#include "pass/MakeCFG.h"
#include "pass/SplitBlocks.h"
#include "util/Util.h"

namespace LL2W::Passes {
	int allocateColoring(Function &function) {
		int spill_count = 0;
		std::unordered_set<int> tried;
		Graph interference;
		while (true) {
			makeInterferenceGraph(function, interference);
			try {
				interference.color(Graph::ColoringAlgorithm::Greedy, WhyInfo::temporaryOffset,
					WhyInfo::savedOffset + WhyInfo::savedCount - 1);
			} catch (const UncolorableError &err) {
				VariablePtr to_spill = selectLowestSpillCost(function, tried);
				if (!to_spill)
					std::terminate();
				std::cerr << "Going to spill " << *to_spill << ". " << function.variableStore.size() << "\n";
				tried.insert(to_spill->id);
				function.addToStack(to_spill, StackLocation::Purpose::Spill);
				if (function.spill(to_spill)) {
					std::cerr << "Spilled. Variables: " << function.variableStore.size() << ". Stack locations: "
					          << function.stack.size() << "\n";
					++spill_count;
					int split = Passes::splitBlocks(function);
					if (0 < split) {
						std::cerr << split << " block" << (split == 1? " was" : "s were") << " split.\n";
						for (BasicBlockPtr &block: function.blocks)
							block->extract();
						Passes::makeCFG(function);
						function.extractVariables(true);
						function.resetLiveness();
						function.computeLiveness();
					} else std::cerr << "No blocks were split.\n";
				} else std::cerr << "Not spilled.\n";
				continue;
			}
			break;
		}

		std::cerr << "Spilling process complete. There " << (spill_count == 1? "was " : "were ") << spill_count << " "
		          << "spill" << (spill_count == 1? ".\n" : "s.\n");

		for (const std::pair<std::string, Node *> &pair: interference) {
			VariablePtr ptr = pair.second->get<VariablePtr>();
			if (ptr->reg == -1)
				ptr->reg = pair.second->color;
			// std::cerr << pair.first << ":" << WhyInfo::registerName(pair.second->color) << (WhyInfo::isSpecialPurpose(pair.second->color)? " !" : "") << "\n";
		}

		return spill_count;
	}

	VariablePtr selectLowestSpillCost(Function &function, const std::unordered_set<int> &avoid) {
		VariablePtr ptr;
		int lowest = -1;
		for (const std::pair<int, VariablePtr> &pair: function.variableStore) {
			const VariablePtr &var = pair.second;
			var->clearSpillCost();
			const int cost = var->spillCost();
			if (cost != -1 && avoid.count(var->id) == 0 && (lowest == -1 || (cost < lowest && !var->isSimple()))) {
				lowest = cost;
				ptr = var;
			}
		}

		return ptr;
	}

	void makeInterferenceGraph(Function &function, Graph &graph) {
		graph.clear();

		for (const std::pair<int, VariablePtr> &pair: function.variableStore) {
			std::cerr << "%% " << pair.first << " " << *pair.second << "\n";
			const std::string id = std::to_string(pair.first);
			Node &node = graph.addNode(id);
			node.data = pair.second;
		}

		std::vector<int> labels;
		labels.reserve(function.variableStore.size());
		for (const std::pair<int, VariablePtr> &pair: function.variableStore)
			labels.push_back(pair.first);

		std::map<int, std::unordered_set<int>> live;

		for (const std::pair<int, VariablePtr> &pair: function.variableStore) {
			if (pair.second->reg != -1)
				continue;
			std::cerr << "Variable " << *pair.second << ":\n";
			for (const std::weak_ptr<BasicBlock> &bptr: pair.second->definingBlocks) {
				live[pair.second->id].insert(bptr.lock()->index);
				std::cerr << "  definer: " << *bptr.lock()->label << " (" << bptr.lock()->index << ")\n";
			}
			for (const std::weak_ptr<BasicBlock> &bptr: pair.second->usingBlocks) {
				live[pair.second->id].insert(bptr.lock()->index);
				std::cerr << "  user: " << *bptr.lock()->label << " (" << bptr.lock()->index << ")\n";
			}
		}

		for (const std::weak_ptr<BasicBlock> &weak: function.blocks) {
			std::shared_ptr<BasicBlock> block = weak.lock();
			if (!block)
				std::cerr << "block is null?\n";
			for (const VariablePtr var: block->liveIn)
				if (var->reg == -1)
					live[var->id].insert(block->index);
			for (const VariablePtr var: block->liveOut)
				if (var->reg == -1)
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

		// static int x = 0;
		// if (++x == 20)
			// std::cout << ("RENDER: interference_" + *function.name + ".png") << "\n";
			// graph.renderTo("interference_" + *function.name + ".png");
	}
}
