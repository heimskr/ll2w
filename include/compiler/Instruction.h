#ifndef COMPILER_INSTRUCTION_H_
#define COMPILER_INSTRUCTION_H_

#include <vector>

#include "parser/Nodes.h"

namespace LL2W {
	class BasicBlock;

	class Instruction {
		private:
			bool extracted = false;

		public:
			BasicBlock *parent = nullptr;
			std::vector<int> read, written;
			const InstructionNode *node;
			/** The order of the instruction within the entire function in its linearized representation. */
			int index;

			Instruction(const InstructionNode *node_, int index_): node(node_), index(index_) {}

			bool isTerminal() const;

			/** Examines the instruction node to determine which virtual registers are read/written. Returns a pair of
			 *  the number of registers read and the number of registers written. */
			std::pair<char, char> extract(bool force = false);

			/** Returns whether this instruction comes before another instruction. */
			bool operator<(const Instruction &) const;
			/** Returns whether this instruction comes after another instruction. */
			bool operator>(const Instruction &) const;
	};
}

#endif
