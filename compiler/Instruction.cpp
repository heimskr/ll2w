#include <iostream>

#include "compiler/Instruction.h"
#include "util/Util.h"

namespace LL2W {
	void Instruction::extract() {
		switch (node->nodeType()) {
			case NodeType::Select: {
				const SelectNode *selectNode = dynamic_cast<const SelectNode *>(node);
				written.push_back(parseLong(selectNode->result));
				break;
			}

			default:
				std::cout << "\e[2m[\e[0;33m!\e[0;2m]\e[0m Unknown instruction type: "
				          << static_cast<int>(node->nodeType());
		}
	}
}