#include <cstdlib>

#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "instruction/SetInstruction.h"
#include "pass/MakeCFG.h"
#include "util/Util.h"

namespace LL2W::Passes {
	CFG & makeCFG(Function &function) {
		function.cfg.clear();
		function.cfg.name = "CFG for " + *function.name;

		// First pass: add all the nodes.
		for (BasicBlockPtr &block: function.blocks) {
			const std::string *label = block->label;
			function.cfg += *label;
			Node &node = function.cfg[*label];
			node.data = std::weak_ptr<BasicBlock>(block);
			block->node = &node;
			function.bbNodeMap.insert({block.get(), &node});
		}

		function.cfg += "exit";

		// Second pass: connect all the nodes.
		for (BasicBlockPtr &block: function.blocks) {
			const std::string *label = block->label;
			for (const std::string *pred: block->preds) {
				if (function.cfg.hasLabel(*pred)) {
					function.cfg.link(*pred, *label);
				} else {
					warn() << "Predicate \e[1m" << *pred << "\e[22m doesn't correspond to any CFG node in function"
				           << " \e[1m" << *function.name << "\e[22m\n";
				}
			}

			if (!block->instructions.empty() && block->instructions.back()->isTerminal())
				function.cfg.link(*label, "exit");
		}

		function.dTree.emplace(function.cfg, function.cfg[0]);
		function.dTree->name = "DTree";
		function.djGraph.emplace(function.cfg, function.cfg[0]);
		function.djGraph->name = "DJ Graph";
		function.mergeSets = function.djGraph->mergeSets((*function.djGraph)[0], (*function.djGraph)["exit"]);
		function.computeSuccMergeSets();
		walkCFG(function, 1000, 0, 1000);
		return function.cfg;
	}

	void walkCFG(Function &function, size_t walks, unsigned int seed, size_t inner_limit) {
		srand(seed == 0? time(NULL) : seed);
		for (size_t walk = 0; walk < walks; ++walk) {
			Node *node = &function.cfg[0];
			Node *end = &function.cfg["exit"];
			size_t count = 0;
			// End the walk once we reach the exit or until we've reached the maximum number of moves allowed per walk.
			while (node != end && ++count <= inner_limit) {
				// Increase the estimated execution count of the node we just walked to.
				++node->get<BasicBlockPtr>()->estimatedExecutions;
				// Check the number of outward edges.
				size_t out_count = node->out().size();
				if (out_count == 0) {
					// If it's somehow zero, the walk is over.
					break;
				} else if (out_count == 1) {
					// If it's just one, simply go to the next node.
					node = *node->out().begin();
				} else {
					// Otherwise, if there are multiple options, choose one randomly.
					node = *std::next(node->out().begin(), rand() % out_count);
				}
			}
		}

		// Increase the random walk counter once we're done doing all the walks.
		function.walkCount += walks;
	}
}
