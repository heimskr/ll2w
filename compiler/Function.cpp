#include <iomanip>
#include <iostream>

#include "parser/ASTNode.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"

namespace LL2W {
	Function::Function(const ASTNode &node) {
		name = node.lexerInfo;
		arguments = dynamic_cast<FunctionHeader *>(node[0])->arguments;
		int label = arguments->arguments.size();
		std::vector<int> preds {};
		std::vector<std::shared_ptr<Instruction>> instructions;
		instructions.reserve(32); // Seems like a reasonable estimate for the number of instructions in a larger block.

		for (const ASTNode *child: *node.at(1)) {
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
			if (!pair.second.definition)
				pair.second.definition = &blocks.front();
		}
	}

	Graph & Function::makeCFG() {
		if (!extracted)
			extract();

		cfg.clear();
		for (BasicBlock &block: blocks) {
			std::string label = std::to_string(block.label);
			cfg += label;
			Node &node = cfg[label];
			node.data = &block;
		}
		return cfg;
	}

	void Function::extract() {
		if (extracted)
			return;

		for (BasicBlock &block: blocks)
			block.extract();
		extractVariables();
		extracted = true;
	}

	Variable & Function::getVariable(int label) {
		if (variableStore.count(label) == 0)
			variableStore.insert({label, Variable(label, nullptr, {})});
		return variableStore.at(label);
	}

	void Function::debug() const {
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
		for (const std::pair<int, Variable> &pair: variableStore) {
			std::cout << "    \e[2m; \e[1m%" << std::left << std::setw(2) << pair.first << "\e[0;2m  def = \e[1m%"
			          << std::setw(2) << pair.second.definition->label << "  \e[0;2muses =";
			for (const BasicBlock *use: pair.second.uses)
				std::cout << " \e[1;2m%" << std::setw(2) << use->label << "\e[0m";
			std::cout << "\e[0m\n";
		}
		std::cout << "}\n\n";
	}
}
