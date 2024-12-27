#include "allocator/ColoringAllocator.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"
#include "pass/MakeCFG.h"
#include "util/Timer.h"
#include "util/Util.h"

#include <cstdlib>

#define CATCH_DTREE

namespace LL2W::Passes {
	CFG & makeCFG(Function &function) {
		Timer timer{"MakeCFG"};

		function.cfg.clear();
		function.cfg.name = "CFG for " + *function.name;
		function.bbNodeMap.clear();

		std::vector<BasicBlockPtr> nice_blocks;
		nice_blocks.reserve(function.blocks.size());

		// First pass: add all the nodes.
		for (const BasicBlockPtr &block: function.blocks) {
			if (block->preds.empty() && block->instructions.size() == 1) {
				if (auto llvm = std::dynamic_pointer_cast<LLVMInstruction>(*block->instructions.begin())) {
					if (llvm->getNodeType() == NodeType::Unreachable) {
						// Sometimes llvm inserts blocks with no preds and no instructions except one `unreachable` instruction.
						// We don't like these blocks because they ruin the D-tree construction.
						// Today is Christmas so we'll put these blocks on the naughty list.
						continue;
					}
				}
			}

			nice_blocks.emplace_back(block);
			const std::string *label = block->getLabel();
			Node &node = function.cfg.addNode(*label);
			node.data = std::weak_ptr(block);
			block->node = &node;
			function.bbNodeMap.emplace(block.get(), &node);
		}

		function.cfg += "exit";

		bool exit_linked = false;

		// Second pass: connect all the nodes.
		for (const BasicBlockPtr &block: nice_blocks) {
			const std::string *label = block->getLabel();
			for (const std::string *pred: block->preds) {
				if (function.cfg.hasLabel(*pred)) {
					function.cfg.link(*pred, *label);
				} else {
					warn() << "Predicate \e[1m" << *pred << "\e[22m doesn't correspond to any CFG node in function \e[1m" << *function.name << "\e[22m\n";
					for (const auto &pair: function.cfg) {
						std::cerr << "- " << pair.first << '\n';
					}
				}
			}

			if (!block->instructions.empty()) {
				InstructionPtr &back = block->instructions.back();
				if (back->isTerminal()) {
					function.cfg.link(*label, "exit");
					exit_linked = true;
				} else if (const LLVMInstruction *llvm = dynamic_cast<LLVMInstruction *>(back.get())) {
					if (llvm->getNodeType() == NodeType::BrUncond) {
						const BrUncondNode *uncond = dynamic_cast<BrUncondNode *>(llvm->getNode());
						if (uncond->destination == label) {
							// The block unconditionally branches to itself, meaning it's an infinite loop.
							// Let's pretend for the sake of the DTree algorithms that it's connected to the exit.
							function.cfg.link(*label, "exit");
							exit_linked = true;
						}
					}
				}
			}
		}

		if (!exit_linked) {
			// Sometimes there's an infinite loop without a block unconditionally branching to itself. The CFG might
			// look like ([Start, A, B, C, Exit] : [Start -> A, A -> B, B -> C, C -> A]). In this case, we just pretend
			// that the final block links to the exit node.
			function.cfg.link(*function.blocks.back()->getLabel(), "exit");
		}

#ifdef CATCH_DTREE
		try {
#endif
			function.dTree.emplace(function.cfg, function.cfg[0]);
#ifdef CATCH_DTREE
		} catch (std::exception &err) {
			function.debug();
			error() << "Constructing DTree failed in function " << *function.name << " for start node "
			        << function.cfg[0].label() << ": " << err.what() << std::endl;
			function.cfg.renderTo("cfg_error.png", "LR");
			throw;
		}
#endif
		function.dTree->name = "DTree";
		function.djGraph.emplace(function.cfg, function.cfg[0]);
		function.djGraph->name = "DJ Graph";
		// Walking the CFG is necessary if we use spill costs for anything.
		// walkCFG(function, 1000, 0, 1000);
		return function.cfg;
	}

	void walkCFG(Function &function, size_t walks, unsigned int seed, size_t inner_limit) {
		Timer timer{"WalkCFG"};
		srand(seed == 0? time(NULL) : seed);
		for (size_t walk = 0; walk < walks; ++walk) {
			Node *node = &function.cfg[0];
			Node *end = &function.cfg["exit"];
			size_t count = 0;
			// End the walk once we reach the exit or until we've reached the maximum number of moves allowed per walk.
			while (node != end && ++count <= inner_limit) {
				// Increase the estimated execution count of the node we just walked to.
				++node->get<std::weak_ptr<BasicBlock>>().lock()->estimatedExecutions;
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
