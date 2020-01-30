#include <iostream>

#include "parser/ASTNode.h"
#include "compiler/Function.h"

namespace LL2W {
	Function::Function(const ASTNode &node) {
		int label = 1;
		std::vector<int> preds {};
		std::vector<const InstructionNode *> instructions;
		instructions.reserve(32); // Seems like a reasonable estimate for the number of instructions in a larger block.

		for (const ASTNode *child: *node.at(1)) {
			if (child->symbol == BLOCKHEADER) {
				blocks.push_back({label, preds, instructions});
				preds.clear();
				instructions.clear();
				const HeaderNode *header = dynamic_cast<const HeaderNode *>(child);
				label = header->label;
				preds = header->preds;
			} else if (const InstructionNode *instruction = dynamic_cast<const InstructionNode *>(child)) {
				instructions.push_back(instruction);
			}
		}
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
			for (const InstructionNode *instruction: block.instructions)
				std::cout << "    " << instruction->debugExtra() << "\n";
		}
	}
}
