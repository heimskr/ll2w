#include <iomanip>
#include <iostream>
#include <unistd.h>

#include "parser/ASTNode.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"

namespace LL2W {
	Function::Function(const ASTNode &node) {
		name = node.lexerInfo;
		arguments = dynamic_cast<FunctionHeader *>(node[0])->arguments;
		astnode = &node;
	}

	void Function::extractBlocks() {
		int label = arguments->arguments.size();
		std::vector<int> preds {};
		std::vector<std::shared_ptr<Instruction>> instructions;
		instructions.reserve(32); // Seems like a reasonable estimate for the number of instructions in a larger block.

		for (const ASTNode *child: *astnode->at(1)) {
			if (child->symbol == BLOCKHEADER) {
				blocks.emplace_back(label, preds, instructions);
				preds.clear();
				instructions.clear();
				const HeaderNode *header = dynamic_cast<const HeaderNode *>(child);
				label = header->label;
				preds = header->preds;
			} else if (const InstructionNode *instruction = dynamic_cast<const InstructionNode *>(child)) {
				instructions.push_back(std::make_shared<Instruction>(instruction));
				instructions.back()->extract();
			}
		}

		if (!instructions.empty())
			blocks.emplace_back(label, preds, instructions);
	}

	void Function::extractVariables() {
		for (BasicBlock &block: blocks) {
			for (int read_var: block.read)
				getVariable(read_var).uses.insert(&block);
			for (int written_var: block.written)
				getVariable(written_var).definition = &block;
		}

		for (std::pair<const int, Variable> &pair: variableStore) {
			// Function arguments aren't defined by any instruction. They're implicitly defined in the first block.
			if (!pair.second.definition) {
				pair.second.definition = &blocks.front();
				blocks.front().written.insert(pair.first);
			}
		}
	}

	void Function::computeSuccMergeSet(Node *node) {
		auto &ms = succMergeSets[node];
		for (Node *succ: node->out()) {
			ms.insert(succ);
			for (Node *m: mergeSets.at(succ))
				ms.insert(m);
			if (succMergeSets.count(succ) == 0)
				computeSuccMergeSet(succ);
		}
	}

	CFG & Function::makeCFG() {
		cfg.clear();
		cfg.name = "CFG";

		// First pass: add all the nodes.
		for (BasicBlock &block: blocks) {
			const std::string label = std::to_string(block.label);
			cfg += label;
			Node &node = cfg[label];
			node.data = &block;
			block.node = &node;
		}

		cfg += "exit";

		// Second pass: connect all the nodes.
		for (BasicBlock &block: blocks) {
			const std::string label = std::to_string(block.label);
			for (int pred: block.preds)
				cfg.link(std::to_string(pred), label);
			if (block.instructions.back()->isTerminal())
				cfg.link(label, "exit");
		}

		dTree.emplace(cfg, cfg[0]);
		dTree->name = "DTree";
		djGraph.emplace(cfg, cfg[0]);
		djGraph->name = "DJ Graph";
		djGraph->renderTo("graph_dj.png");
		mergeSets = djGraph->mergeSets((*djGraph)[0], (*djGraph)["exit"]);
		computeSuccMergeSets();
		for (const Node::Map &map: {mergeSets, succMergeSets}) {
			std::cout << "--------------------------------\n";
			for (const std::pair<Node *, Node::Set> &pair: map) {
				std::cout << pair.first->label() << ":";
				for (Node *node: pair.second)
					std::cout << " " << node->label();
				std::cout << "\n";
			}
		}
		return cfg;
	}

	void Function::computeSuccMergeSets() {
		computeSuccMergeSet(&djGraph.value()[*getEntry().node]);
	}

	void Function::extract() {
		if (extracted)
			return;

		extractBlocks();
		for (BasicBlock &block: blocks)
			block.extract();
		extractVariables();
		makeCFG();
		computeLiveness();
		extracted = true;
	}

	Variable & Function::getVariable(int label) {
		if (variableStore.count(label) == 0)
			variableStore.insert({label, Variable(label, nullptr, {})});
		return variableStore.at(label);
	}

	BasicBlock & Function::getEntry() {
		return blocks.front();
	}

	void Function::computeLiveness() {
		if (livenessComputed)
			return;

		livenessComputed = true;
		for (std::pair<const int, Variable> &pair: variableStore) {
			for (BasicBlock &block: blocks) {
				isLiveIn(block, pair.second);
				isLiveOut(block, pair.second);
			}
		}
	}

	bool Function::isLiveIn(BasicBlock &block, Variable &var) {
		// M^r(block) = M(block) ∪ {block}; // Create a new set from the merge set
		Node::Set m_r = mergeSets.at(block.node);
		m_r.insert(block.node);

		// Iterate over all the uses of var
		// for t ∈ uses(var) do
		for (BasicBlock *t: var.uses) {
			// while t≠def(var) do
			while (t != var.definition) {
				// if t ∩ M^r(block) then
				if (m_r.count(t->node) > 0) {
					block.liveIn.insert(&var);
					return true;
				}
				// t = dom-parent(t); // Climb up from node t in the DJ-Graph
				t = cfg[*(*dTree)[*t->node].parent()].get<BasicBlock *>();
			}
		}

		return false;
	}

	bool Function::isLiveOut(BasicBlock &block, Variable &var) {
		// if def(a)=n
		if (var.definition == &block) {
			// return uses(a)\def(a)≠∅;
			return !(var.uses.empty() || (var.uses.size() == 1 && 0 < var.uses.count(var.definition)));
		}

		// for t ∈ uses(a) do // Iterate over all the uses of a
		for (BasicBlock *t: var.uses) {
			// while t≠def(a) do
			while (t != var.definition) {
				// if t ∩ Ms(n) then
				if (0 < succMergeSets.at(block.node).count(t->node)) {
					block.liveOut.insert(&var);
					return true;
				}
				// t = dom-parent(t);
				t = cfg[*(*dTree)[*t->node].parent()].get<BasicBlock *>();
			}
		}

		return false;
	}

	void Function::debug() {
		std::cout << "\e[1m" << *name << "\e[0m(";
		std::vector<FunctionArgument> &args = arguments->arguments;
		for (auto begin = args.begin(), iter = begin, end = args.end(); iter != end; ++iter) {
			if (iter != begin)
				std::cout << "\e[2m,\e[0m ";
			std::cout << *iter->type;
			if (iter->name)
				std::cout << " " << *iter->name;
		}
		std::cout << ") {\n";
		for (const BasicBlock &block: blocks) {
			std::cout << "    \e[2m; \e[4m<label>:\e[1m" << block.label << "\e[0;2;4m: preds = ";
			for (auto begin = block.preds.begin(), iter = begin, end = block.preds.end(); iter != end; ++iter) {
				if (iter != begin)
					std::cout << ", ";
				std::cout << " %" << *iter;
			}
			std::cout << "\e[0m\n";
			for (const std::shared_ptr<Instruction> &instruction: block.instructions) {
				int read, written;
				std::tie(read, written) = instruction->extract();
				std::cout << "\e[s    " << instruction->node->debugExtra() << "\e[u\e[2m" << read << " " << written
				          << "\e[0m\n";
			}
			std::cout << "\n";
		}
		std::cout << "    \e[2m; Variables:\e[0m\n";
		for (std::pair<const int, Variable> &pair: variableStore) {
			std::cout << "    \e[2m; \e[1m%" << std::left << std::setw(2) << pair.first << "\e[0;2m  def = \e[1m%"
			          << std::setw(2) << pair.second.definition->label << "  \e[0;2muses =";
			for (const BasicBlock *use: pair.second.uses)
				std::cout << " \e[1;2m%" << std::setw(2) << use->label << "\e[0m";
			std::cout << "\e[0m\n";
			std::cout << "    \e[2m;      \e[32min  =\e[1m";
			for (const BasicBlock &block: blocks) {
				if (0 < block.liveIn.count(&pair.second))
					std::cout << " %" << block.label;
			}
			std::cout << "\e[0m\n";
			std::cout << "    \e[2m;      \e[31mout =\e[1m";
			for (const BasicBlock &block: blocks) {
				if (0 < block.liveOut.count(&pair.second))
					std::cout << " %" << block.label;
			}
			std::cout << "\e[0m\n";
		}
		std::cout << "}\n\n";
		cfg.renderTo("graph_" + *name + ".png");
	}
}
