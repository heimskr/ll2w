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
				const HeaderNode *header = dynamic_cast<const HeaderNode *>(child);
				blocks.emplace_back(label, preds, instructions);
				instructions.clear();
				label = header->label;
				preds = header->preds;
			} else if (const InstructionNode *instruction = dynamic_cast<const InstructionNode *>(child)) {
				instructions.push_back(instruction);
			}
		}
	}
}
