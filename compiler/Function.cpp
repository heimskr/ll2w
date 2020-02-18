#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <unistd.h>

#include "parser/ASTNode.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"
#include "compiler/LLVMInstruction.h"

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
		int offset = 0;
		int instructionIndex = 0;

		std::function<void(BasicBlock &)> finishBlock = [&](BasicBlock &block) {
			block.offset = offset;
			block.parent = this;
			for (std::shared_ptr<Instruction> &instruction: instructions) {
				instruction->parent = &block;
				instruction->extract();
				for (std::vector<VariablePtr> variables: {instruction->read, instruction->written}) {
					for (VariablePtr &vptr: variables)
						variableStore.insert({vptr->id, vptr});
				}
			}
		};

		for (const ASTNode *child: *astnode->at(1)) {
			if (child->symbol == BLOCKHEADER) {
				blocks.emplace_back(label, preds, instructions);
				finishBlock(blocks.back());
				offset += instructions.size();
				preds.clear();
				instructions.clear();
				const HeaderNode *header = dynamic_cast<const HeaderNode *>(child);
				label = header->label;
				preds = header->preds;
			} else if (const InstructionNode *instruction = dynamic_cast<const InstructionNode *>(child)) {
				instructions.push_back(std::make_shared<LLVMInstruction>(instruction, instructionIndex++));
				linearInstructions.push_back(instructions.back());
			}
		}

		if (!instructions.empty()) {
			blocks.emplace_back(label, preds, instructions);
			finishBlock(blocks.back());
		}
	}

	void Function::extractVariables() {
		std::cout << "\e[1;4m" << *name << "\e[0m\n";
		for (BasicBlock &block: blocks) {
			for (VariablePtr read_var: block.read) {
				std::cout << "\e[2m" << read_var.get() << "\e[0m " << block.label << ": " << std::string(*read_var->type) << " %" << read_var->id << "\n";
				read_var->usingBlocks.insert(&block);
			}
			for (VariablePtr written_var: block.written)
				written_var->definingBlock = &block;
			for (std::shared_ptr<Instruction> &instruction: block.instructions) {
				for (VariablePtr read_var: instruction->read) {
					read_var->lastUse = instruction.get();
					read_var->uses.insert(instruction.get());
				}
			}
		}

		for (std::pair<const int, VariablePtr> &pair: variableStore) {
			// Function arguments aren't defined by any instruction. They're implicitly defined in the first block.
			if (!pair.second->definingBlock) {
				pair.second->definingBlock = &blocks.front();
				blocks.front().written.insert(pair.second);
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

	Node & Function::operator[](const BasicBlock &bb) const {
		return *bbMap.at(&bb);
	}

	int Function::arity() const {
		return arguments? arguments->arguments.size() : 0;
	}

	bool Function::variadic() const {
		return arguments? arguments->ellipsis : false;
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
			bbMap.insert({&block, &node});
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
		mergeSets = djGraph->mergeSets((*djGraph)[0], (*djGraph)["exit"]);
		computeSuccMergeSets();
		walkCFG(1000, 0, 1000);
		return cfg;
	}

	void Function::walkCFG(size_t walks, unsigned int seed, size_t inner_limit) {
		srand(seed == 0? time(NULL) : seed);
		for (size_t walk = 0; walk < walks; ++walk) {
			Node *node = &cfg[0];
			Node *end = &cfg["exit"];
			size_t count = 0;
			while (node != end && ++count <= inner_limit) {
				++node->get<BasicBlock *>()->estimatedExecutions;
				size_t out_count = node->out().size();
				if (out_count == 0) {
					break;
				} else if (out_count == 1) {
					node = *node->out().begin();
				} else {
					node = *std::next(node->out().begin(), rand() % out_count);
				}
			}
		}
		walkCount += walks;
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

	VariablePtr Function::getVariable(int label) {
		return variableStore.at(label);
	}

	BasicBlock & Function::getEntry() {
		return blocks.front();
	}

	CallingConvention Function::getCallingConvention() const {
		return variadic()? CallingConvention::StackOnly : CallingConvention::Reg16;
	}

	void Function::computeLiveness() {
		if (livenessComputed)
			return;

		livenessComputed = true;
		for (std::pair<const int, VariablePtr> &pair: variableStore) {
			for (BasicBlock &block: blocks) {
				isLiveIn(block, pair.second);
				isLiveOut(block, pair.second);
			}
		}
	}

	bool Function::isLiveIn(BasicBlock &block, VariablePtr var) {
		// M^r(block) = M(block) ∪ {block}; // Create a new set from the merge set
		Node::Set m_r = mergeSets.at(block.node);
		m_r.insert(block.node);

		// Iterate over all the uses of var
		// for t ∈ uses(var) do
		for (BasicBlock *t: var->usingBlocks) {
			// while t≠def(var) do
			while (t != var->definingBlock) {
				// if t ∩ M^r(block) then
				if (m_r.count(t->node) > 0) {
					block.liveIn.insert(var);
					return true;
				}
				// t = dom-parent(t); // Climb up from node t in the DJ-Graph
				BasicBlock *t_new = cfg[*(*dTree)[*t->node].parent()].get<BasicBlock *>();
				if (t_new == t)
					break;
				t = t_new;
			}
		}

		return false;
	}

	bool Function::isLiveOut(BasicBlock &block, VariablePtr var) {
		// if def(a)=n
		if (var->definingBlock == &block) {
			// return uses(a)\def(a)≠∅;
			return !(var->usingBlocks.empty() ||
				(var->usingBlocks.size() == 1 && 0 < var->usingBlocks.count(var->definingBlock)));
		}

		// for t ∈ uses(a) do // Iterate over all the uses of a
		for (BasicBlock *t: var->usingBlocks) {
			// while t≠def(a) do
			while (t != var->definingBlock) {
				// if t ∩ Ms(n) then
				if (0 < succMergeSets.at(block.node).count(t->node)) {
					block.liveOut.insert(var);
					return true;
				}
				// t = dom-parent(t);
				BasicBlock *t_new = cfg[*(*dTree)[*t->node].parent()].get<BasicBlock *>();
				if (t_new == t)
					break;
				t = t_new;
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
			std::cout << "    \e[2m; \e[4m<label>:\e[1m" << block.label << "\e[0;2;4m @ " << block.offset <<
			             ": preds =";
			for (auto begin = block.preds.begin(), iter = begin, end = block.preds.end(); iter != end; ++iter) {
				if (iter != begin)
					std::cout << ",";
				std::cout << " %" << *iter;
			}
			std::cout << "\e[0m\n";
			for (const std::shared_ptr<Instruction> &instruction: block.instructions) {
				int read, written;
				std::tie(read, written) = instruction->extract();
				std::cout << "\e[s    " << instruction->debugExtra() << "\e[u\e[2m" << read << " " << written
				          << "\e[0m\n";
			}
			std::cout << "\n";
		}
		std::cout << "    \e[2m; Variables:\e[0m\n";
		for (std::pair<const int, VariablePtr> &pair: variableStore) {
			std::cout << "    \e[2m; \e[1m%" << std::left << std::setw(2) << pair.first << "\e[0;2m  def = \e[1m%"
			          << std::setw(2) << pair.second->definingBlock->label << "  \e[0;2muses =";
			for (const BasicBlock *use: pair.second->usingBlocks)
				std::cout << " \e[1;2m%" << std::setw(2) << use->label << "\e[0m";
			int spill_cost = pair.second->spillCost();
			std::cout << "\e[2m  cost = " << (spill_cost == INT_MAX? "∞" : std::to_string(spill_cost)) << "\e[0m " << pair.second.get() << "\n";
			std::cout << "    \e[2m;      \e[32min  =\e[1m";
			for (const BasicBlock &block: blocks) {
				if (0 < block.liveIn.count(pair.second))
					std::cout << " %" << block.label;
			}
			std::cout << "\e[0m\n";
			std::cout << "    \e[2m;      \e[31mout =\e[1m";
			for (const BasicBlock &block: blocks) {
				if (0 < block.liveOut.count(pair.second))
					std::cout << " %" << block.label;
			}
			std::cout << "\e[0m\n";
		}
		std::cout << "}\n\n";
		for (Node *node: cfg.nodes()) {
			if (node->data.has_value()) {
				BasicBlock *bb = node->get<BasicBlock *>();
				if (bb)
					node->rename("\"" + node->label() + ":" + std::to_string(bb->estimatedExecutions) + "\"");
			}
		}
		cfg.renderTo("graph_" + *name + ".png");
		dTree->renderTo("graph_D_" + *name + ".png");
	}

	void Function::debugMergeSets() const {
		for (const Node::Map &map: {mergeSets, succMergeSets}) {
			std::cout << "--------------------------------\n";
			for (const std::pair<Node *, Node::Set> &pair: map) {
				std::cout << pair.first->label() << ":";
				for (Node *node: pair.second)
					std::cout << " " << node->label();
				std::cout << "\n";
			}
		}
	}
}
