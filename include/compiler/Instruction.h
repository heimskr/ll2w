#ifndef COMPILER_INSTRUCTION_H_
#define COMPILER_INSTRUCTION_H_

#include <vector>

#include "parser/Nodes.h"

namespace LL2W {
	class Instruction {
		private:
			bool extracted = false;

		public:
			std::vector<int> read, written;
			const InstructionNode *node;

			Instruction(const InstructionNode *node_): node(node_) {}

			/** Examines the instruction node to determine which virtual registers are read/written. Returns a pair of
			 *  the number of registers read and the number of registers written. */
			std::pair<char, char> extract();
	};
}

#endif
