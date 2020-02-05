#include <iomanip>
#include <iostream>

#include "parser/ASTNode.h"
#include "compiler/Function.h"
#include "compiler/Instruction.h"

namespace LL2W {
	Function::Function(const ASTNode &node) {
		int label = dynamic_cast<const FunctionHeader *>(node[0])->arguments->arguments.size();
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

	void Function::debug() const {
		for (const BasicBlock &block: blocks) {
			std::cout << "\e[4m; <label>:" << block.label << ": preds = ";
			for (auto begin = block.preds.begin(), iter = begin, end = block.preds.end(); iter != end; ++iter) {
				if (iter != begin)
					std::cout << ", ";
				std::cout << " %" << *iter;
			}
			std::cout << "\e[0m\n";
			for (const std::shared_ptr<Instruction> &instruction: block.instructions) {
				int read, written;
				std::tie(read, written) = instruction->extract();
				std::cout << "\e[s       " << instruction->node->debugExtra() << "\e[u\e[2m" << std::setw(2) << read
				          << " " << std::setw(2) << written << "\e[0m\n";
			}
		}
	}
}
