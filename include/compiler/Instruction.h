#ifndef COMPILER_INSTRUCTION_H_
#define COMPILER_INSTRUCTION_H_

#include <vector>

#include "parser/Nodes.h"

namespace LL2W {
	class Instruction {
		std::vector<int> read, written;
		const InstructionNode *node;

		Instruction(const InstructionNode *node_): node(node_) {}

		/** Examines the instruction node to determine which virtual registers are read/written. */
		void extract();
	};
}

#endif
